#include "tc_client.h"


void tc_client::initAddr() {	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(tc_port); 
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
}


void tc_client::initSock() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
       		perror("client.socket() error");
		std::exit(1);
    	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	       		perror("client.connect() error");
			std::exit(2);
	}
}

void tc_client::processing() {
	for(int i=0;i<RETRY_COUNT;i++) {
		initSock();
		request="["+getCurDT()+"] "+tc_name;
		send(sock,request.c_str(),request.length()+1,0);		
		std::cout<<"sended:"<<request<<std::endl;
		close(sock);
		sleep(tc_period);	
	}
}

void tc_client::setOptions(int argc, char** argv) {
	if (argc<4) {
		std::cout<<"wrong parameters, using:\n"
			<<"tc_client <username> <port> <interval_sec>\n";
		std::exit(0);
	} else {
		tc_name=std::string(argv[1]);
		tc_port=std::atoi(argv[2]);
		tc_period=std::atoi(argv[3]);
		std::cout<<"username: "<<tc_name<<std::endl
			<<"port: "<<tc_port<<std::endl
			<<"reconnect interval, sec: "<<tc_period<<std::endl
			<<"retry count: "<<RETRY_COUNT<<std::endl
			<<"---------------------------\n";
	}
}

std::string getCurDT() {
    	auto now = std::chrono::system_clock::now();
    	auto in_time_t = std::chrono::system_clock::to_time_t(now);
    	std::stringstream ss;    
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");    
	return ss.str();
}

int main(int argc, char** argv) {
	tc_client cl1;
	cl1.setOptions(argc, argv);
	cl1.initAddr();
	cl1.processing();
	return 0;
}
