#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <iostream>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int abc = bind(fd, (sockaddr *)&addr, sizeof(addr));
    if (abc < 0)
    {
        return -1;
    }
    listen(fd, 1024);
    int max = 0;
    pollfd fds[1024];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    for (int i = 1; i < 1024; i++)
    {
        fds[i].fd = -1;
    }
    std::cout << "yes1" << std::endl;
    while (1)

    {
        int n = poll(fds, max + 1, -1);
        if (n < 0)
        {
            if (errno == EINTR) //stop by signal
            {
                continue;
            }
            break;
        }
        // have link
        if (fds[0].revents == POLLIN && fds[0].fd != -1)
        {
            int cfd = accept(fd, nullptr, nullptr);
            for (int i = 1; i < 1024; i++)
            {
                if (fds[i].fd == -1)
                {
                    fds[i].fd = cfd;
                    fds[i].events = POLLIN;
                    if (max < i)
                    {
                        max = i;
                    }
                    break;
                } //link more than max
                if (i == 1024)
                {
                    close(cfd);
                    continue;
                }
                if (--n == 0)
                {
                    continue;
                }
            }
        } //send message
        for (int k = 1; k < max + 1; k++)
        {
            if (fds[k].revents == POLLIN && fds[k].fd != -1)
            {

                char buf[64];
                int a = read(fds[k].fd, buf, 64);
                write(fds[k].fd, "\nfuck", sizeof("\nfuck"));
                if (a <= 0)
                {
                    fds[k].fd = -1;
                    continue;
                }
                printf("%s\n", buf);
            }
        }
    }
}