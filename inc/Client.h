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

    ~Client() {}
};

#endif /* CLIENT_H_ */