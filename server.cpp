#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PORT 8000
#define BACKLOG_NUM 50

using namespace std;

void error_handler(){
	cout << "error has occured\n";
	perror(strerror(errno));
}

int main(){
	int socketnum;
	socketnum = socket(AF_INET, SOCK_STREAM, 0);
	cout << "socket num: " << socketnum << "\n";
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SOCK_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int resp =bind(socketnum, (struct sockaddr *)&addr, sizeof(addr));
	if(resp != 0){
		cout << "problem with binding\n";
		cout << resp << "\n";
		perror(strerror(errno));
	}
	if(listen(socketnum, BACKLOG_NUM) != 0){
		cout << "problem with listen\n";
	}	

	bool cont = true;

	while(cont){
		struct sockaddr_in new_addr;
		int new_addr_size = sizeof(new_addr);
	        int * new_addr_size_ptr = & new_addr_size;
		int new_socket_num = accept(socketnum, (struct sockaddr *)& new_addr, (socklen_t *)new_addr_size_ptr);
		cout << new_socket_num << "\n";
		char buffer[1024];
		if(read(new_socket_num, buffer, 1024)== -1){
			error_handler();
		}
		cout << buffer << "\n";	
		char hello[] = "hi back";
		if(send(new_socket_num, hello, strlen(hello),0)== -1){
			error_handler();
		}
		close(new_socket_num);	
	}
	close(socketnum);
	
	return 0;
}

//void respond(char request[], )

