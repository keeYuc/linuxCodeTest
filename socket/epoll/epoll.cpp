#include <sys/epoll.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    bind(fd, (sockaddr *)&addr, sizeof(addr));
    listen(fd, 1024);
    //epoll
    int tree = epoll_create(1024);
    epoll_event event;
    epoll_event outEvent[1024];
    event.data.fd = fd;
    event.events = EPOLLIN;
    epoll_ctl(tree, EPOLL_CTL_ADD, fd, &event);
    while (1)
    {
        int n = epoll_wait(tree, outEvent, 1024, -1);
        std::cout << "yes1" << std::endl;
        if (n <= 0)
        {
            if (errno == ECONNABORTED || errno == EINTR)
            {
                continue;
            }
            break;
        }
        for (int i = 0; i < n; i++)
        {
            //have accept
            if (outEvent[i].data.fd == fd)
            {
                int readFd = accept(fd, nullptr, nullptr);
                event.data.fd = readFd;
                event.events = EPOLLIN;
                epoll_ctl(tree, EPOLL_CTL_ADD, readFd, &event);
                std::cout << "yes2" << std::endl;
                continue;
            }
            //have message
            if (outEvent[i].data.fd != fd)
            {
                std::cout << "yes3" << std::endl;
                int tempFd = outEvent[i].data.fd;
                char buff[64];
                int n = read(tempFd, buff, 64);
                if (n <= 0)
                {
                    epoll_ctl(tree, EPOLL_CTL_DEL, tempFd, nullptr);
                    close(tempFd);
                }
                printf("%s\n", buff);
                write(tempFd, "ATK", sizeof("ATK"));
            }
        }
    }
}