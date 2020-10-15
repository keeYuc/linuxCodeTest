#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        mkfifo("/myfifo", 0664);
        int fd = open("./myfifo", O_RDWR);
        write(fd, "fuck123", sizeof("fuck123"));
        sleep(10);
        std::cout << wait(NULL) << std::endl;
    }
    if (pid == 0)
    {
        std::cout << getpid() << std::endl;
        std::fstream myfile;
        int fd = open("./myfifo", O_RDWR);
        char a[1024];
        read(fd, a, 1024);
        printf("%s", a);
        std::cout << "zi gao wan" << std::endl;
    }
    else if (pid < 0)
    {
        std::cout << "fuck" << std::endl;
    }

    return 0;
}