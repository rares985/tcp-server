#ifndef ECHO_HANDLER_H_
#define ECHO_HANDLER_H_

#include "Handler.h"

class EchoHandler : public Handler
{
    int handle(epoll_event e) override
    {
        if (e.events & EPOLLHUP)
        {
            /* Remove from list in IOLoop */
            return -1;
        }

        if (e.events & EPOLLERR)
        {
            return -1;
        }

        if (e.events & EPOLLOUT)
        {
        }

        if (e.events & EPOLLIN)
        {
        }
    }
};

#endif /* ECHO_HANDLER_H_ */