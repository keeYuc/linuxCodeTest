#include<event2/event.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void myAccept(short s, int i, void* ptr)
{

}
int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(int));
    sockaddr_in addr;
    addr.sin_port = htons(9999);
    inet_pton(AF_INET, "133.0.0.1", &addr.sin_addr.s_addr);
    int err = bind(fd, (sockaddr*) &addr, sizeof(addr));
    if (err <= 0)
    {
        std::cout << "bind err !!" << std::endl;
        return -1;
    }
    listen(fd, 1024);
    //
    event_base* base = event_base_new();

    event* events = event_new(base, fd, 0, myAccept, )
        event_add(events, nullptr);
        





}
