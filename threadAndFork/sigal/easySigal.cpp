#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <iostream>
void fuckChild(int a)
{
    std::cout << wait(NULL) << std::endl;
}
int main()
{

    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << getpid() << std::endl;
        sleep(2);
    }
    if (pid > 0)
    {
        signal(SIGCHLD, fuckChild);
        sleep(10);
    }
    return 0;
}