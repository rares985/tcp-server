#include "IOManager.h"

IOManager::IOManager() : epfd_{epoll_create(1)}
{
    // TODO: Still needed ??
    // this->epfd_ = epoll_create(1);
}

void IOManager::Loop()
{
    while (true)
    {
        int nfds = epoll_wait(this->epfd_, this->events_, this->kMaxEvents_, -1);
        for (int i = 0; i < nfds; i++)
        {
            int fd = this->events_[i].data.fd;
            Handle(fd, this->events_[i]);
        }
    }
}

void IOManager::AddHandler(int fd, unsigned int events)
{
    epoll_event e;
    e.data.fd = fd;
    e.events = events;

    errno = 0;
    int ret = epoll_ctl(this->epfd_, EPOLL_CTL_ADD, fd, &e);
    if (ret < 0)
    {
        std::cout << "Error in epoll_ctl: " << strerror(errno) << "\n";
    }
}

void IOManager::RemoveHandler(int fd)
{
    epoll_event e;
    e.data.fd = fd;
    e.events = 0;

    int ret = epoll_ctl(this->epfd_, EPOLL_CTL_DEL, fd, &e);
    if (ret < 0)
    {
        std::cout << "Error in epoll_ctl: " << strerror(errno) << "\n";
    }
}
