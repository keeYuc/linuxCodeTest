#include <iostream>
#include <unistd.h>
#include <pthread.h>

int sum;
void *fuck1(void *arg)
{
    for (int i = 0; i < 500000; i++)
    {
        int temp = sum;
        temp++;
        sum = temp;
    }
    std::cout << sum << std::endl;
    return nullptr;
}
void *fuck2(void *arg)
{
    for (int i = 0; i < 500000; i++)
    {
        int temp = sum;
        temp++;
        sum = temp;
    }
    std::cout << sum << std::endl;
    return nullptr;
}
int main()
{
    pthread_t gab1;
    pthread_t gab2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&gab1, nullptr, fuck1, nullptr);
    pthread_create(&gab2, nullptr, fuck2, nullptr);
    pthread_join(gab1, nullptr);
    pthread_join(gab2, nullptr);
    std::cout << sum << std::endl;

    return 0;
}