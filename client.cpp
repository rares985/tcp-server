#include <iostream>

#include "Client.h"
#include "IOLoop.h"
#include <unistd.h>

int main()
{
    const char *host = "127.0.0.1";
    int port = 13131;

    Client client{host, port};

    client.Connect();

    return 0;
}