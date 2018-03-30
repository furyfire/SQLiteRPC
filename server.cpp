#include <iostream>
#include "abstractstubserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <sqlite3.h>

using namespace jsonrpc;
using namespace std;

sqlite3 *db;
Json::Value object;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    Json::Value row;
    for (int i = 0; i < argc; i++) {
        row[azColName[i]] = argv[i] ? argv[i] : NULL;
    }
    object.append(row);
    return 0;
}

class MyStubServer : public AbstractStubServer {
public:
    MyStubServer(AbstractServerConnector &connector);

    virtual Json::Value query(const std::string& sql);
    virtual std::string ping();
};

MyStubServer::MyStubServer(AbstractServerConnector &connector) : AbstractStubServer(connector) {}

Json::Value MyStubServer::query(const std::string& sql) {
    cout << "Query received: " << sql << endl;
    object.clear();
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cout << "SQL error: " << zErrMsg << endl;
        string error_message(zErrMsg);
        sqlite3_free(zErrMsg);
        throw JsonRpcException(1, error_message);
    }
    return object;
}

string MyStubServer::ping() {
    cout << "Got ping!" << endl;
    return "pong";
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Please supply path to an SQLite3 database file" << endl;
        return EXIT_FAILURE;
    }

    int rc = sqlite3_open(argv[1], &db);
    if (rc) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    HttpServer httpserver(8383);
    MyStubServer s(httpserver);
    s.StartListening();

    while(1) {} //Listen forever
}