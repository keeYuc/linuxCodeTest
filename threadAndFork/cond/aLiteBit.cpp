#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
pthread_cond_t condt
    PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex
    PTHREAD_MUTEX_INITIALIZER;
void *user(void *arg)
{
    while (1)
    {
        pthread_cond_wait(&condt, &mutex);
        std::vector<int> *p1;
        p1 = (std::vector<int> *)arg;
        int a = p1->back();
        p1->pop_back();
        pthread_mutex_unlock(&mutex);
        std::cout << "using-----" << a << std::endl;
        sleep(2);
    }
    return nullptr;
}
void *prod(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        std::vector<int> *p1;
        p1 = (std::vector<int> *)arg;
        int a = rand() % 100;
        p1->push_back(a);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condt);
        std::cout << "prob-----" << a << std::endl;
        sleep(2);
    }
    return nullptr;
}
int main()
{

    srand(time(nullptr));
    std::vector<int> slice;
    slice.resize(200);
    pthread_t gab;
    pthread_t gab1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&gab1, nullptr, prod, &slice);
    pthread_create(&gab, nullptr, user, &slice);
    pthread_join(gab, nullptr);
    pthread_join(gab1, nullptr);
    pthread_cond_destroy(&condt);
}