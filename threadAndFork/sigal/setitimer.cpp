#include <sys/time.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
void fuck(int a)
{
    std::cout << a << std::endl;
}
int main()
{
    signal(SIGALRM, fuck);
    itimerval time1;
    time1.it_interval.tv_sec = 0;
    time1.it_interval.tv_usec = 500000;
    time1.it_value.tv_sec = 1;
    time1.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &time1, nullptr);
    while (1)
    {
        sleep(1);
    }
}