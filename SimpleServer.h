#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define BACKLOG_NUM_DEFAULT 50

class SimpleServer{
public:
        const in_port_t DEFAULT_PORT_NUM = htons(8000);
        const uint32_t DEFAULT_IP_ADDRESS = htonl(INADDR_LOOPBACK);
        SimpleServer();
        SimpleServer(int port);
        int getSockNum();
        int startServer();
        int nextConnection();
        std::vector<char>&  nextMessage(std::vector<char>& msg);
        int sendMessage(std::vector<char> & msg);
        void closeClientSocket();
        void closeSocket();
        void closeAll();
private:
        int sock, client_sock;
        in_port_t port;
        uint32_t address;
        char buffer[1024];
};

