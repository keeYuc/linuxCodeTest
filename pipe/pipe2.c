
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int pipfd[2];

    pipe(pipfd);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(pipfd[1]);
        char str[64];
        sleep(1);
        read(pipfd[0], str, 64);
        printf("%s", str);
    }

    if (pid > 0)
    {
        close(pipfd[0]);

        int flag = fcntl(pipfd[1], F_GETFL, 0);
        flag |= O_NONBLOCK;
        fcntl(pipfd[1], F_SETFL, flag);
        write(pipfd[1], "abc", sizeof("abc"));
    }

    return 0;
}