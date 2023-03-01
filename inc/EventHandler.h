#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <sys/epoll.h>

class EventHandler
{
public:
    virtual void Handle(int fd, epoll_event e) = 0;
};

#endif /* EVENT_HANDLER_H_ */