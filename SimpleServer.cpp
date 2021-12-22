#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "SimpleServer.h"

	int SimpleServer::startServer(){
		//make a socket, bind and listens
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0){return -1;}
 		struct sockaddr_in addr;
        	addr.sin_family = AF_INET;
        	addr.sin_port = port;
        	addr.sin_addr.s_addr = address;
        	if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){return -2;}
		if(listen(sock, BACKLOG_NUM_DEFAULT) < 0){return -3;}
		return 0;		
	}
	
	SimpleServer::SimpleServer():sock{-1}, client_sock{-1}, port{DEFAULT_PORT_NUM}, address{DEFAULT_IP_ADDRESS}{}
	SimpleServer::SimpleServer(int port){port = htons(port);}
	int SimpleServer::getSockNum(){return sock;}
	int SimpleSErver::nextConnection(){
		struct sockaddr_in c_addr;
                int c_addr_size = sizeof(c_addr);
                int * c_addr_size_ptr = &c_addr_size;
                client_sock = accept(sock, (struct sockaddr *)& c_addr, (socklen_t *)c_addr_size_ptr);
		return client_sock;
	}
	std::vector<char>& SimpleServer::nextMessage(std::vector<char>& msg){
		if(sock < 0 || client_sock < 0){return msg;}
		int cur_len = 0;
		while((cur_len = read(client_sock, buffer, 1024)) > 0){
			msg.insert(msg.end(), buffer, buffer + cur_len); 
		}
		return msg;	
	}
	int SimpleServer::sendMessage(std::vector<char> & msg){
		if(sock < 0 || client_sock < 0){return -1;}
		char * msg_sent = new char[msg.size()]{};
		memcpy(msg_sent, msg.data(), msg.size());
		send(client_sock, msg_sent, msg.size(), 0);
		return 0;	
	}
	void SimpleServer::closeClientSocket(){
		if(client_sock >= 0){
			close(client_sock);
		}
	}
	void SimpleServer::closeSocket(){
		if(sock >= 0){
			close(sock);
		}
	}
	void SimpleServer::closeAll(){
		closeSocket();
		closeClientSocket();
	}
