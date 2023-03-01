#include <iostream>

#include "Server.h"
#include "IOLoop.h"
#include <unistd.h>

int main()
{
    const char *host = "127.0.0.1";
    int port = 13131;

    TCPServer s{host, port};

    return 0;
}