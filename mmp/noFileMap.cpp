#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    auto p = mmap(nullptr, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED)
    {
        perror("map faild");
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        char b1[64];
        memcpy(b1, p, 64);
        printf("%s\n", b1);
    }
    if (pid > 0)
    {
        memcpy(p, "abc", strlen("abc"));
        wait(NULL);
        munmap(p, 1024);
    }

    return 0;
}