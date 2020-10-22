#include <pthread.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
sem_t sem;

void *using1(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
        std::vector<int> *p1;
        p1 = (std::vector<int> *)arg;

        int a = p1->back();
        p1->pop_back();

        std::cout << "using1-----" << a << std::endl;
        sleep(2);
    }
    return nullptr;
}
void *using2(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
        std::vector<int> *p1;
        p1 = (std::vector<int> *)arg;

        int a = p1->back();
        p1->pop_back();

        std::cout << "using2-----" << a << std::endl;
        sleep(2);
    }
    return nullptr;
}
void *prod(void *arg)
{
    while (1)
    {

        std::vector<int> *p1;
        p1 = (std::vector<int> *)arg;
        int a = rand() % 100 + 1;
        p1->push_back(a);
        sem_post(&sem);
        std::cout << "prob-----" << a << std::endl;
        sleep(1);
    }
    return nullptr;
}
int main()
{
    sem_init(&sem, 0, 0);
    srand(time(nullptr));
    std::vector<int> slice;
    slice.resize(200);
    pthread_t gab;
    pthread_t gab1;
    pthread_t gab2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&gab, nullptr, prod, &slice);
    pthread_create(&gab1, nullptr, using1, &slice);
    pthread_create(&gab2, nullptr, using2, &slice);

    pthread_join(gab, nullptr);
    pthread_join(gab1, nullptr);
    pthread_join(gab2, nullptr);
}