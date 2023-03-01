#include <iostream>

#include "Server.h"
#include "IOManager.h"
#include <unistd.h>

int main()
{
    const char *host = "127.0.0.1";
    int port = 13131;

    TCPServer s{host, port};

    s.Loop();

    return 0;
}