#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <iostream>

int main()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    connect(fd, (sockaddr *)&addr, sizeof(addr));
    char buff[64];
    int a;
    while (1)
    {

        memset(buff, 0, 64);
        std::cin >> buff;
        a = write(fd, buff, strlen(buff));
        if (a <= 0)
        {
            close(fd);
            break;
        }
        memset(buff, 0, 64);
        read(fd, buff, 64);
        printf("%s\n", buff);
    }
}