#include <sys/epoll.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    //port overuse
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));
    bind(fd, (sockaddr*) &addr, sizeof(addr));
    listen(fd, 1024);
    //epoll
    int tree = epoll_create(1024);
    epoll_event event;
    epoll_event outEvent[1024];
    event.data.fd = fd;
    //et mode
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(tree, EPOLL_CTL_ADD, fd, &event);
    while (1)
    {
        int n = epoll_wait(tree, outEvent, 1024, -1);
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
                int flag = fcntl(readFd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(readFd, F_SETFL, flag);
                event.data.fd = readFd;
                event.events = EPOLLIN | EPOLLET; //et mode
                epoll_ctl(tree, EPOLL_CTL_ADD, readFd, &event);

                continue;
            }

            while (outEvent[i].data.fd != fd)
            {
                char buff[1024];
                int n = read(outEvent[i].data.fd, buff, 1024);
                if (n == -1)
                {

                    break;
                }
                if (n <= 0 && n != -1)
                {
                    epoll_ctl(tree, EPOLL_CTL_DEL, outEvent[i].data.fd, nullptr);
                    close(outEvent[i].data.fd);

                    continue;
                }
                printf("%s\n", buff);
            }
            write(outEvent[i].data.fd, "ATK", sizeof("ATK"));
        }
    }
}