#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
void fuck(int a)
{
    std::cout << a << std::endl;
}
void fuck1(int a)
{
    std::cout << "fuck" << std::endl;
}
int main()
{
    struct sigaction mys;
    struct sigaction mys1;
    mys.sa_handler = fuck;
    mys1.sa_handler = fuck1;
    mys.sa_flags = 0;
    sigemptyset(&mys.sa_mask);
    sigaction(SIGALRM, &mys, nullptr);
    mys1.sa_flags = 0;
    sigemptyset(&mys1.sa_mask);
    alarm(1);
    sleep(10);
    itimerval it;
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_usec = 0;
    it.it_value.tv_sec = 1;
    it.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &it, nullptr);
    sigaction(SIGUSR1, &mys1, nullptr);
    sleep(10);
    raise(SIGUSR1);
}