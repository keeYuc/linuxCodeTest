#include <sys/epoll.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include<fcntl.h>
namespace myLoopEpoll
{
    const int maxLink = 1024;
}
//*获取监听文件描述符
int getSocketId(char* buff, int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(a));
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, buff, &addr.sin_addr.s_addr);
    bind(fd, (sockaddr*) &addr, sizeof(addr));
    listen(fd, myLoopEpoll::maxLink);
    return fd;
}
epoll_event& setEpoll_Event(int fd, void* func)
{
    epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    event.data.ptr = func;
    return event;
}
void Accept(int tree, int temp)
{   //!注意释放
    auto event = new epoll_event;

    event->data.ptr = Action;
    event->events = EPOLLIN;
    int cfd = accept(temp, nullptr, nullptr);
    event->data.fd = cfd;
    epoll_ctl(tree, EPOLL_CTL_ADD, cfd, event);
}
void Action(int tree, int temp)
{
    while (1)
    {
        char buff[1024];
        int flag = fcntl(temp, F_GETFL);
        flag |= O_NONBLOCK;
        fcntl(flag, F_SETFL);
        int n = read(temp, buff, 1024);
        if (n <= 0)
        {
            return;
            write(temp, "yes", sizeof("yes"));
        }
        printf(buff, 1024);
    }
epoll_event events[myLoopEpoll::maxLink];
int main()
{
    int fd = getSocketId("127.0.0.1", 8888);
    int tree = epoll_create(myLoopEpoll::maxLink);
    auto event = setEpoll_Event(fd, Accept);
    while (1)
    {
        int n = epoll_wait(tree, events, myLoopEpoll::maxLink, -1);
        for (int i = 0;i < n;i++)
        {
            auto coolback = (void(*)(int, int))events[n].data.ptr;
            coolback(tree, events[n].data.fd);
        }
    }

}

