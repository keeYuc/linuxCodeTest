#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>

int main()
{

    // mkfifo("./fuck.txt", 777);
    int fd = open("./fuck.txt", O_RDWR);

    printf("%d\n", fd);
    pid_t pid = fork();
    if (pid == 0)
    {
        int fd = open("./fuck.txt", O_RDWR);
        sleep(2);
        char str[64];
        memset(str, 0, 64);
        int n = read(fd, str, 64);
        printf("%s   and %d     is:\n", str, n);
    }
    if (pid > 0)
    {

        int b = write(fd, "123", strlen("123"));
        printf("  %d\n", b);
        b = write(fd, "123", strlen("123"));
        printf("  %d\n", b);
        b = write(fd, "123", strlen("123"));
        printf("  %d\n", b);
        b = write(fd, "123", strlen("123"));
        printf("  %d\n", b);

        close(fd);
        auto a = wait(NULL);

        printf("%d   %d\n", a, b);
    }

    return 0;
}