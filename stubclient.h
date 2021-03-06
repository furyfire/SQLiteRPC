/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_STUBCLIENT_H_
#define JSONRPC_CPP_STUB_STUBCLIENT_H_

#include <jsonrpccpp/client.h>

class StubClient : public jsonrpc::Client
{
    public:
        StubClient(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        Json::Value query(const std::string& sql) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["sql"] = sql;
            Json::Value result = this->CallMethod("query",p);
            if (result.isArray())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        std::string ping() throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p = Json::nullValue;
            Json::Value result = this->CallMethod("ping",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_STUBCLIENT_H_
