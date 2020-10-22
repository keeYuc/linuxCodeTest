#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/mman.h>
#include <string.h>
int main()
{

    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(5);
        int a = open("./mmpFuck", O_RDWR);
        int len = lseek(a, 0, SEEK_END);
        void *p = mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, a, 0);
        close(a);
        if (p == MAP_FAILED)
        {
            perror(" read  fuck");
            return -1;
        }
        char b1[5];
        printf("%s", (char *)p);
        memset(b1, 0, 5);
        memcpy(b1, p, 5);
        printf("%s", b1);

        printf("%p\n", p);
    }

    if (pid > 0)
    {
        int a = open("./mmpFuck", O_RDWR);
        int len = lseek(a, 0, SEEK_END);
        void *p = mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, a, 0);
        close(a);
        if (p == MAP_FAILED)
        {
            perror(" write  fuck");
            return -1;
        }
        memcpy(p, "hello", strlen("hello"));
        printf("%s\n", (char *)p);
        printf("%p\n", p);
        wait(NULL);

        munmap(p, 3);
    }
    return 0;
}