#include "IOLoop.h"

IOLoop::IOLoop()
{

    this->epfd_ = epoll_create(1);
}

void IOLoop::Loop()
{
    while (true)
    {
        int nfds = epoll_wait(this->epfd_, this->events_, this->kMaxEvents_, -1);
        for (int i = 0; i < nfds; i++)
        {
            int fd = this->events_[i].data.fd;
            Handler *h = handlers_[fd];
            h->handle(this->events_[i]);
        }
    }
}

void IOLoop::AddHandler(int fd, Handler *h, unsigned int events)
{
    handlers_[fd] = h;
    epoll_event e;
    e.data.fd = fd;
    e.events = events;

    int ret = epoll_ctl(this->epfd_, EPOLL_CTL_ADD, fd, &e);
}

void IOLoop::RemoveHandler(int fd)
{
    handlers_.erase(fd);
}
