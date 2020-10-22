#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <iostream>

void fuckChild(int a)
{
    std::cout << "fuck" << std::endl;
}
int main()
{
    // signal(SIGALRM, fuckChild);
    alarm(1);
    alarm(4);
    alarm(5);
    sleep(10);
    alarm(10);
    // std::cout << "fuck123" << std::endl;

    return 0;
}