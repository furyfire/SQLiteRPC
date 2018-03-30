#include <iostream>

#include "stubclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3) {
        cout << "Please provide an url and a query" << endl;
        return EXIT_FAILURE;
    }
    
    HttpClient httpclient(argv[1]);
    StubClient c(httpclient);
    try
    {
        cout << "Sending ping" << endl;
        cout << c.ping() << endl;
    }
    catch (JsonRpcException e)
    {
        cerr << e.what() << endl;
    }
    
    try
    {
        cout << "Sending query" << endl;
        string query(argv[2]);
        cout << c.query(query) << endl;
    }
    catch (JsonRpcException e)
    {
        cerr << e.what() << endl;
    }
}