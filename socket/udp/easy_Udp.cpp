#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<printf.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>


int main()
{

    char buff[64];
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr;
    sockaddr_in cilentAddr;
    socklen_t len;
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    bind(fd, (sockaddr*) &addr, sizeof(addr));
    while (1)
    {
        bzero(buff, 64);
        int n = recvfrom(fd, buff, 64, 0, (sockaddr*) &cilentAddr, &len);
        printf("%s -----%d\n", buff, n);
        sendto(fd, buff, strlen(buff), 0, (sockaddr*) &cilentAddr, len);
    }
}