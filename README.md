# Install
```shell
sudo apt-get install libjsonrpccpp-dev libjsonrpccpp-tools sqlite3

git clone https://github.com/furyfire/SQLiteRPC

cd SQLiteRPC

make CONF=SERVER
make CONF=CLIENT
cd dist/Debug/GNU-Linux

#For the server
./sqliterpc my_database.db

#For the client
./sqliterpcclient localhost 8383 "CREATE TABLE test (id int);"
```

# Test commands
curl -d "{\"jsonrpc\":\"2.0\",\"method\":\"query\",\"params\":{\"sql\":\"INSERT INTO test2 VALUES (4);\"},\"id\":3}" -o - localhost:8383
curl -d "{\"jsonrpc\":\"2.0\",\"method\":\"query\",\"params\":{\"sql\":\"SELECT * FROM test2;\"},\"id\":3}" -o - localhost:8383
curl -d "{\"jsonrpc\":\"2.0\",\"method\":\"ping\",\"id\":3}" -o - localhost:8383


