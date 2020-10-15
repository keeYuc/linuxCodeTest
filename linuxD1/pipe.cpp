#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <stdio.h>

int main()
{

    int mypipe[2];
    pipe(mypipe);
    pid_t pid1 = fork();
    if (pid1 > 0)
    {

        close(mypipe[0]);
        sleep(5);
        write(mypipe[1], "nibi", sizeof("nibi"));

        pid_t a1 = wait(NULL);
        std::cout << "fu--- " << a1 << std::endl;
    }
    if (pid1 == 0)
    {
        std::cout << getpid() << std::endl;
        close(mypipe[1]);
        char *a[1024];
        read(mypipe[0], a, 1024);
        std::cout << a << std::endl;
        printf("%s----", a);
        std::cout << "zi --- " << std::endl;
    }

    return 0;
}
