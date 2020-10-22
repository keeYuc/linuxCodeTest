#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(a));
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    int err = bind(fd, (sockaddr *)&addr, sizeof(addr));
    if (err < 0)
    {
        printf("bind err%d\n", err);
        return 0;
    }
    //kaishi  select
    int max = fd;
    fd_set readfds;
    fd_set tempfds;
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    listen(fd, 10);
    while (1)
    {
        tempfds = readfds;
        int n = select(max + 1, &tempfds, nullptr, nullptr, nullptr);
        if (n < 0)
        {
            if (errno == ECONNABORTED || errno == EINTR)
            {
                continue;
            }
            break;
        } //you link
        if (FD_ISSET(fd, &tempfds))
        {
            int acfd = accept(fd, nullptr, nullptr);
            printf("%d accepy yes\n", acfd);
            FD_SET(acfd, &readfds); // linsten->>>read fd
            if (max < acfd)
            {

                max = acfd;
            }
            if (--n == 0) //only one fd change
            {
                continue;
            }
        }

        for (int i = fd + 1; i <= max; i++) //have string
        {
            printf("%d for yes\n", i);
            if (FD_ISSET(i, &tempfds))
            {
                char buff[64];
                while (1)
                {
                    int nread = read(i, buff, 64);
                    write(i, "yes", sizeof("yes"));
                    if (nread <= 0)
                    {
                        FD_CLR(i, &readfds);
                        close(i);
                        break;
                        //pop unuse fd and close
                    }
                    printf("%s\n", buff);
                    if (--n == 0) //only one fd change
                    {
                        continue;
                    }
                }
            }
        }
    }
}