#include <iostream>

#include "Client.h"
#include "IOManager.h"
#include <unistd.h>

int main()
{
    const char *host = "127.0.0.1";
    int port = 13131;

    Client client{host, port};

    client.Connect();

    char buffer[512]{0};
    snprintf(buffer, 512, "%s", "Hey there!");

    while (true)
    {
        usleep(2 * 1000 * 1000);
        int ret = client.Send(reinterpret_cast<unsigned char *>(&buffer[0]), 512);
        if (ret < 0)
        {
            break;
        }
    }

    return 0;
}