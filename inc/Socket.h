#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <arpa/inet.h>

class Socket
{
private:
    int fd_;
    const char *host_;
    int port_;
    sockaddr_in addr_;

public:
    Socket(const char *host, int port) : host_{host}, port_{port}
    {
        fd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (fd_ < 0)
        {
            std::cout << "Error creating socket";
        }

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port_);
        inet_pton(AF_INET, host_, &addr_.sin_addr);
        // TODO: err
    }

    ~Socket()
    {
        if (fd_ > 0)
        {
            close(fd_);
        }
    }

    int Accept()
    {
        sockaddr_in addr;
        socklen_t addrlen;

        int client_fd = accept(fd_, (struct sockaddr *)&addr, &addrlen);

        return client_fd;
    }

    int Bind()
    {
        int ret = bind(fd_, (sockaddr *)&addr_, sizeof(addr_));
        // TODO: err
        return ret;
    }

    std::string HostAndPort()
    {
        std::stringstream ss;
        ss << host_ << ":" << port_;
        return ss.str();
    }

    int Listen(int max_clients = 5)
    {
        errno = 0;
        int ret = listen(fd_, max_clients);
        if (ret < 0)
        {
            std::cout << "Error in listen on " << HostAndPort() << " errno (" << errno << ")";
        }
        else
        {
            std::cout << "Listening on " << HostAndPort() << "\n";
        }
    }

    void Connect()
    {
        std::stringstream ss;
        errno = 0;
        int ret = connect(fd_, (struct sockaddr *)&addr_, sizeof(addr_));
        if (ret < 0)
        {
            ss << "Failure when connecting to " << host_ << ":" << port_ << " errno (" << errno << ")";
            std::cout << ss.str();
        }
    }

    int MakeNonBlocking()
    {
        return fcntl(fd_, F_SETFD, fcntl(fd_, F_GETFD, 0) | O_NONBLOCK);
    }

    void SetRecvTimeout(int sec = 5, int usec = 0)
    {
        timeval tv{sec, usec};
        int ret = setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
    }

    void SetSendTimeout(int sec = 5, int usec = 0)
    {
        timeval tv{sec, usec};
        int ret = setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
    }

    int Fd() { return fd_; }
};
#endif /* SOCKET_H_ */