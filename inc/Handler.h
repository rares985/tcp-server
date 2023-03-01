#ifndef HANDLER_H_
#define HANDLER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>

class Handler
{
public:
    virtual int handle(epoll_event e) = 0;
};

#endif /* HANDLER_H_ */