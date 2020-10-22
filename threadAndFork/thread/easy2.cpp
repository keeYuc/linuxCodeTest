#include <pthread.h>
#include <iostream>
#include <unistd.h>
void *fuck(void *arg)
{
    sleep(15);
    std::cout << "im" << *(int *)arg << std::endl;
    return nullptr;
}

int main()
{
    pthread_t firet;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int a1[5];
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    for (int a = 0; a < 5; a++)
    {
        a1[a] = a;
        pthread_create(&firet, &attr, fuck, &a1[a]);
    }
    sleep(20);
    return 0;
}