#include "tc_server.h"

tc_server::tc_server() {
	tc_port=4444;
	msg_read=0;
	logfile.open("log.txt",std::ios::out|std::ios::in|std::ios::trunc);
	if (!logfile.is_open()) {
		perror("cant initialize logfile");
		exit(1);
	}
}

tc_server::~tc_server() {
	if (acc_sock) close(acc_sock);
	close(listener);
	logfile.close();

}


void tc_server::setOptions(int argc, char** argv) {
        if (argc<2) {
                std::cout<<"wrong parameters, using:\n"
                        <<"tc_server <listen_port>\n";
                std::exit(0);
        } else {
            
                tc_port=std::atoi(argv[1]);
                std::cout<<"listen port "<<tc_port<<std::endl
			<<"message limit "<<MSG_LIMIT<<std::endl
                	<<"---------------------------\n";
        }
}

void tc_server::getListenSocket() {
        int result;
        sockaddr_in local;

        listener= socket(AF_INET, SOCK_STREAM, 0);
        if (listener<0) {
                perror("server.socket() error");
                std::exit(1);
        }

        local.sin_family = AF_INET;
        local.sin_port = htons(tc_port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        result = bind( listener, (sockaddr*) &local, sizeof(local) );
        if (result<0) {
                perror("server.bind() error");
                std::exit(1);
        }

        result = listen(listener,1);	// 1 accepted socket for 1 fork;
        if (result) {
                perror("server.listen() error");
                std::exit(1);
        }

}

void tc_server::processing() {
	while(msg_read<MSG_LIMIT) {

        	acc_sock = accept(listener, NULL, NULL);
        	if(acc_sock < 0) {
            		perror("server.accept() error");
		        exit(3);
       		} 

	
        	switch(fork())
        	{
        	case -1:
            		perror("server.fork() error");
		        break;

	        case 0:
        		close(listener);
			std::cout<<"fork "<<getpid()<<" start\n";
                        recv(acc_sock,request,BUF_SIZE, 0);
		        writeLog();
			std::cout<<"fork "<<getpid()<<" finish\n\n";
			 			
		        close(acc_sock);
           		exit(0);
		default:
			msg_read++;
			close(acc_sock);
						
        	}
		std::cout<<"messages read:"<<msg_read<<std::endl;

    	}
}

void tc_server::writeLog() {
	logfile<<request<<std::endl;
	std::cout<<"writed:"<<request<<std::endl;
}


int main(int argc, char** argv) {
	tc_server srv1;
	srv1.setOptions(argc, argv);
	srv1.getListenSocket();
	srv1.processing();
	return 0;

}

