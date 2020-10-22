#include <pthread.h>
#include <iostream>
#include <unistd.h>
void *abc1(void *arg)
{
    sleep(20);
    std::cout << pthread_self() << std::endl;
    return nullptr;
}

int main()
{
    pthread_t first;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&first, &attr, abc1, nullptr);
    //pthread_detach(first);
    // std::cout << pthread_cancel(first) << std::endl;

    sleep(30);
    // void *ptr;
    // int a = pthread_join(first, &ptr);
    // std::cout << a << ptr << std::endl;
}
