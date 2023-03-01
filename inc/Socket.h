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

        char buf[INET_ADDRSTRLEN]{0};
        inet_ntop(AF_INET, (char *)&(addr.sin_addr), buf, sizeof(addr));
        std::cout << "[" << client_fd << "]";
        std::cout << "connected with " << buf << " : " << ntohs(addr.sin_port) << "\n ";

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
            std::cout << "[" << fd_ << "]";
            std::cout << "Listening on " << HostAndPort() << "\n";
        }
        return ret;
    }

    void Connect()
    {
        errno = 0;
        int ret = connect(fd_, (struct sockaddr *)&addr_, sizeof(addr_));
        if (ret < 0)
        {
            std::cout << "Failure when connecting to " << host_ << ":" << port_ << " " << strerror(errno);
        }
    }

    int MakeNonBlocking(int /* fd */)
    {
        return fcntl(fd_, F_SETFD, fcntl(fd_, F_GETFD, 0) | O_NONBLOCK);
    }

    void SetRecvTimeout(int sec = 5, int usec = 0)
    {
        timeval tv{sec, usec};

        errno = 0;
        int ret = setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
        if (ret < 0)
        {
            std::cout << "Error in setsockopt: " << strerror(errno) << "\n";
        }
    }

    void SetSendTimeout(int sec = 5, int usec = 0)
    {
        timeval tv{sec, usec};
        errno = 0;
        int ret = setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
        if (ret < 0)
        {
            std::cout << "Error in setsockopt: " << strerror(errno) << "\n";
        }
    }

    inline ssize_t Receive(unsigned char *buf, size_t bufsiz)
    {
        return Receive(fd_, buf, bufsiz);
    }

    ssize_t Receive(int fd, unsigned char *buf, size_t bufsiz)
    {
        ssize_t n = 0;
        ssize_t total = 0;
        while (total < static_cast<ssize_t>(bufsiz))
        {
            errno = 0;
            n = recv(fd, buf, bufsiz - total, 0);
            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    break;
                }
                else
                {
                    std::cout << "Error when reading " << strerror(errno) << "\n";
                    return -1;
                }
            }

            if (n == 0)
            {
                return 0;
            }

            buf += n;
            total += n;
        }

        return total;
    }

    inline ssize_t Send(unsigned char *buf, size_t len)
    {
        return Send(fd_, buf, len);
    }

    ssize_t Send(int fd, unsigned char *buf, size_t len)
    {
        size_t total = 0;
        ssize_t bytes_left = len;
        ssize_t n = 0;

        while (total < len)
        {
            errno = 0;
            n = send(fd, buf + total, bytes_left, MSG_NOSIGNAL);
            if (n == -1)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    break;
                }
                else
                {
                    std::cout << "Error when sending " << strerror(errno) << "\n";
                    return -1;
                }
            }
            total += n;
            bytes_left -= n;
        }

        return total;
    }

    int Fd() { return fd_; }
};
#endif /* SOCKET_H_ */