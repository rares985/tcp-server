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
#include "EventHandler.h"
#include "IOManager.h"

class TCPServer : public IOManager, public EventHandler
{
private:
    Socket sock_;

    std::map<int, EventHandler *> clients_;

public:
    TCPServer(const char *host, int port, int max_clients = 5) : sock_{host, port}
    {
        sock_.MakeNonBlocking(2);
        sock_.Bind();
        sock_.Listen(max_clients);

        AddHandler(sock_.Fd(), EPOLLIN | EPOLLOUT | EPOLLET);
    }

    ~TCPServer()
    {
    }

    void Handle(int fd, epoll_event ev) override
    {
        if (fd == sock_.Fd())
        {
            /* New connection, accept it */
            int client_fd = sock_.Accept();
            // TODO: Make nonblocking
            // clients_[client_fd] = new Handler(); // TODO? Yes or no keep it?
            AddHandler(client_fd, EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLHUP);
        }
        else if (ev.events & (EPOLLRDHUP | EPOLLHUP))
        {
            std::cout << "[" << fd << "]";
            std::cout << "Client disconnected\n";
            /* Don't monitor this fd anymore */
            RemoveHandler(fd);
        }
        else if (ev.events & EPOLLIN)
        {
            /* Read */
            Read(fd);
        }
        else
        {
            std::cout << "Unexpected events " << ev.events << "\n";
        }
    }

    void Read(int fd)
    {
        unsigned char buf[512]{0};
        sock_.Receive(fd, buf, sizeof(buf));
        std::cout << "[" << fd << "]";
        std::cout << "Received " << buf << "\n";
    }
};

#endif /* SERVER_H_ */