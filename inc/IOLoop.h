#ifndef IO_LOOP_H_
#define IO_LOOP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "Handler.h"

class IOLoop
{
private:
    static constexpr int kMaxEvents_ = 32;

    int epfd_;
    std::map<int, Handler *> handlers_;
    struct epoll_event events_[kMaxEvents_];

public:
    IOLoop();

    void Loop();

    void AddHandler(int fd, Handler *h, unsigned int events);
    void RemoveHandler(int fd);
};

#endif /* IO_LOOP_H_ */