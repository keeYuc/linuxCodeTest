
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pipfd[2];
    pipe(pipfd);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(pipfd[1]);
        char str[64];
        read(pipfd[0], str, 64);
        printf("%s", str);
    }

    if (pid > 0)
    {
        close(pipfd[0]);
        write(pipfd[1], "abc", sizeof("abc"));
    }

    return 0;
}