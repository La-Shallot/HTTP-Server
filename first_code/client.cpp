#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PORT 8000

using namespace std;

int main(){
	int sock = 0;
	struct sockaddr_in serv_addr;
	char hello[] = "Hello Buddy";
	char buffer[1024];
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "error with creating sock\n";
	}	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SOCK_PORT);
	

	int resp = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(resp < 0){
		cout << "error with connection\n";
		cout << resp;
	}
	
	send(sock, hello, strlen(hello), 0);
	cout << "SEnd message \n";

	long returnval;
	cout << "Receiving Message\n";
	returnval = read(sock, buffer, 1024);
	cout << returnval << "\n";
	cout << buffer << "\n";
	close(sock);
	return 0;
}
