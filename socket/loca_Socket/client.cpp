#include<iostream>
#include<sys/socket.h>
#include<string.h>
#include<sys/un.h>
#include<unistd.h>



int main()
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);

    char buff[64];


    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "./fuck");
    connect(fd, (sockaddr*) &addr, sizeof(addr));
    while (1)
    {
        write(fd, buff, 64);
        printf("%s", buff);
        bzero(buff, 64);
        std::cin >> buff;

        bzero(buff, 64);
        read(fd, buff, 64);

    }

}