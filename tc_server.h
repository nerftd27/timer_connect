#ifndef TC_SERVER_H
#define TC_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>
#include <unistd.h>     //close(socket)
#include <cstdlib>      //std::exit()
#include <iostream>
#include <fcntl.h>
#include <fstream>

const unsigned int BUF_SIZE=1024;


class tc_server {
        int listener;
        int acc_sock;
        int msg_read;
	

        unsigned int tc_port;
        char request [BUF_SIZE];
        std::fstream logfile;


        void getListenSocket();
        void writeLog();
public:
        tc_server();
        void processing();
        void setOptions(int argc, char** argv);
        ~tc_server();

};

#endif //TC_SERVER_H
