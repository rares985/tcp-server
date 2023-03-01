#ifndef CLIENT_H_
#define CLIENT_H_

#include "Socket.h"

class Client
{
private:
    Socket sock_;

public:
    Client(const char *host, int port) : sock_{host, port} {}

    void Connect()
    {
        sock_.Connect();
    }

    int Send(unsigned char *buf, size_t len)
    {
        ssize_t ret = sock_.Send(sock_.Fd(), buf, len);
        std::cout << "Sent " << ret << "bytes\n";
        return ret;
    }

    int Recv(unsigned char *buf, size_t bufsiz)
    {
        ssize_t ret = sock_.Receive(buf, bufsiz);
        std::cout << "Received " << ret << "bytes\n";
        return ret;
    }

    ~Client()
    {
    }
};

#endif /* CLIENT_H_ */