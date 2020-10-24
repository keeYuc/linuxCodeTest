#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<printf.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<ctype.h>
#include<sys/time.h>


int main()
{

    char buff[64];
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    while (1)
    {
        timeval start, bigen;
        bzero(buff, 64);
        memcpy(buff, "a", 1);
        sleep(1);
        sendto(fd, buff, strlen(buff), 0, (sockaddr*) &addr, len);
        gettimeofday(&start, nullptr);
        int n = recvfrom(fd, buff, 64, 0, (sockaddr*) &addr, &len);
        gettimeofday(&bigen, nullptr);


        printf("(%ld/1000)ms -----\n", -(start.tv_usec - bigen.tv_usec));

    }

}