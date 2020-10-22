#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

void fuck(int a)
{
    std::fstream fd;
    fd.open("/home/keey/myCode/linuxCodeTest/daemom/abc.txt", std::ios::out | std::ios::app);

    time_t time1;
    time(&time1);
    auto abc = ctime(&time1);
    fd.write(abc, strlen(abc));
    fd.close();
}
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(2);
        setsid();
        chdir("/");
        umask(0000);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        struct sigaction abc;
        abc.sa_flags = 0;
        sigemptyset(&abc.sa_mask);
        abc.sa_handler = fuck;
        sigaction(SIGALRM, &abc, nullptr);
        itimerval timer;
        timer.it_interval.tv_sec = 1;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = 2;
        timer.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, nullptr);
        while (1)
        {
            sleep(1);
        }
    }

    if (pid > 0)
    {
        std::cout << "zhu jing cheng tui chu!!!\nmy pid is:" << getpid() << std::endl;
    }
}
