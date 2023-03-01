#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>

#include "Socket.h"

class TCPServer
{
private:
    Socket sock_;

public:
    TCPServer(const char *host, int port, int max_clients = 5) : sock_{host, port}
    {
        sock_.MakeNonBlocking();
        sock_.Bind();
        sock_.Listen(max_clients);
    }

    // int Accept()
    // {
    //     sockaddr_in addr;
    //     socklen_t addrlen = sizeof(addr);
    //     int client_fd = accept(fd_, (struct sockaddr *)&addr, &addrlen);

    //     char buf[INET_ADDRSTRLEN]{0};
    //     inet_ntop(AF_INET, (char *)&(addr.sin_addr), buf, sizeof(addr));
    //     std::cout << "[+] connected with " << buf << ":" << ntohs(addr.sin_port) << "\n";

    //     return client_fd;
    // }

    ~TCPServer()
    {
    }
};

#endif /* SERVER_H_ */