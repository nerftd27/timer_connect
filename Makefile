all: tc_server tc_client

tc_server: tc_server.cpp
	g++ -g -Wall tc_server.cpp -o tc_server

tc_client: tc_client.cpp
	g++ -g -Wall tc_client.cpp -o tc_client
