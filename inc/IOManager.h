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
#include <iostream>

#include "EventHandler.h"

class IOManager
{
private:
    static constexpr int kMaxEvents_ = 32;

    int epfd_;
    epoll_event events_[kMaxEvents_];

protected:
    IOManager();
    void AddHandler(int fd, unsigned int events);
    void RemoveHandler(int fd);

    virtual void Handle(int fd, epoll_event ev) = 0;

public:
    IOManager(const IOManager &other) = delete;

    void Loop();
};

#endif /* IO_LOOP_H_ */