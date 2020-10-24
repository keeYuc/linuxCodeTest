#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<sys/un.h>
#include<iostream>
#include<unistd.h>



int main()
{
    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "./fuck");
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    unlink("./fuck");
    int err1 = bind(fd, (sockaddr*) &addr, sizeof(addr));
    if (err1 < 0)
    {
        std::cout << "fuck you bind err!" << std::endl;
        return -1;
    }
    listen(fd, 1024);
    char buff[64];
    while (1)
    {
        bzero(buff, 64);
        int cfd = accept(fd, nullptr, nullptr);
        write(cfd, "link ok\n", sizeof("link ok\n"));
        while (1)
        {
            bzero(buff, 64);
            int n = read(cfd, buff, 64);
            if (n <= 0)//!客户端关闭后只会往后走一行代码 没有判断就会直接退出
            {
                std::cout << "client out or link err!" << std::endl;
                close(cfd);
                break;
            }
            write(cfd, "message ok\n", sizeof("message ok\n"));
            printf("%s【%d】\n", buff, n);



        }

    }

}