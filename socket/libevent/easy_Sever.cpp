#include<event2/event.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

event* ev1;
void myRead(evutil_socket_t fd, short events, void* arg)
{
    char buff[64];


    bzero(buff, 64);
    int n = read(fd, buff, 64);
    write(fd, buff, 64);
    if (n <= 0)
    {
        std::cout << "link lost" << std::endl;
        event_del(ev1);

        close(fd);
        return;

    } else
    {
        printf("%s", buff);
    }


}
void myAccept(evutil_socket_t fd, short events, void* arg)
{

    int cfd = accept(fd, nullptr, nullptr);
    if (cfd > 0)
    {
        ev1 = event_new((event_base*) arg, cfd, EV_READ | EV_PERSIST, myRead, nullptr);

        event_add(ev1, nullptr);
    }
}
int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int err = bind(fd, (sockaddr*) &addr, sizeof(addr));
    if (err < 0)
    {
        std::cout << "bind err !!" << err << std::endl;
        return -1;
    }
    listen(fd, 1024);
    //
    event_base* base = event_base_new();


    event* events = event_new(base, fd, EV_READ | EV_PERSIST, myAccept, base);
    if (events == nullptr)
    {
        std::cout << "event_new err !!" << std::endl;
        return -1;
    }
    event_add(events, nullptr);
    event_base_dispatch(base);






}
