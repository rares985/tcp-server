#ifndef ACCEPT_HANDLER_H_
#define ACCEPT_HANDLER_H_

#include "Handler.h"

class AcceptHandler : public Handler
{
    virtual int handle(epoll_event e)
    {
    }
};

#endif /* ACCEPT_HANDLER_H_ */