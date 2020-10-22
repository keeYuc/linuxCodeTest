#include <iostream>
#include <unistd.h>
#include <pthread.h>

int sum;
void *fuck1(void *arg)
{
}
void *fuck2(void *arg)
{
}
int main()
{ //new begin
    // pthread_mutex_init(&mutex, NULL);
    //new end
    pthread_rwlock_t rwlock;
    pthread_rwlock_init(&rwlock, nullptr);
    pthread_rwlock_rdlock(&rwlock);
    pthread_rwlock_wrlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);
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
    pthread_attr_destroy(&attr);
    pthread_rwlock_destroy(&rwlock);

    return 0;
}