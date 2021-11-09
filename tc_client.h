#ifndef TC_CLIENT_H
#define TC_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>      //std::exit()
#include <iostream>
#include <unistd.h>

//for getCurDT()
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string

const char SERVER_IP[] = "127.0.0.1";
const int RETRY_COUNT=5;


class tc_client {
        std::string tc_name;
        int sock;
        struct sockaddr_in addr;
        unsigned int tc_period;
        unsigned int tc_port;
        std::string request;

        void initSock();
public:
        tc_client();
        void processing();
        void initAddr();
	void setOptions(int argc,char** argv);
};

std::string getCurDT();

#endif //TC_CLIENT_H
