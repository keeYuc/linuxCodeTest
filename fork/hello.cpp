#include <iostream>
#include <unistd.h>

int main()
{
    std::cout << "fuck you baby " << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "fuck you baby " << std::endl;
        sleep(1);
    }
    return 0;
}