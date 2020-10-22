#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <wait.h>

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            sleep(1);
            std::cout << "I'm child my fuck id is :" << getpid() << "my fuck ppid is->>>" << getppid() << std::endl;
            // execlp("sl", NULL);
            auto a = execl("/home/keey/myCode/linuxCodeTest/fork/fuck", "fuck", NULL);
            std::cout << "i should not in here!!!" << std::endl;
        }
        if (pid > 0)
        {
            while (1)
            {

                pid_t child_Pid = waitpid(-1, NULL, WNOHANG);
                if (child_Pid > 0)
                {
                    std::cout << "I'm fuck this child his pid is:" << child_Pid << std::endl;
                }
                else if (child_Pid < 0)
                {
                    break;
                }
            }
        }
    }

    return 0;
}