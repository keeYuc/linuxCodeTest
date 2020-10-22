#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <iostream>
#include <pthread.h>
int fd = socket(AF_INET, SOCK_STREAM, 0);
sockaddr_in addr;
sockaddr clilAddr;
socklen_t len = sizeof(addr);
char str1[16];
void *fuck(void *arg)
{
    int fd2 = *(int *)arg;
    while (1)
    {
        inet_ntop(AF_INET, &addr.sin_addr.s_addr, str1, 16);
        ntohs(addr.sin_port);
        printf("%s:", str1);
        printf("%d\n", ntohs(addr.sin_port));
        char str[64];
        memset(str, 0, 64);
        int n = read(fd2, str, 64);
        write(fd2, "fuck\n", strlen("fuck\n"));

        printf("%s\n", str);
        if (n < 0)
        {
            close(fd2);
            pthread_exit(nullptr);
        }
    }
    return arg;
}
int main()
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    // addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));
    bind(fd, (sockaddr *)&addr, sizeof(addr));
    listen(fd, 10);

    pthread_t pthread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    while (1)
    {
        int fd2 = accept(fd, (sockaddr *)&addr, &len);
        pthread_create(&pthread, &attr, fuck, &fd2);
    }
    close(fd);
    return 0;
}
