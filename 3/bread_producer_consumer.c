#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>          
#include <sys/stat.h>

#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10
#define BUFFER_SIZE 5

sem_t *emptySlots;
sem_t *fullSlots;
sem_t *mutex;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

void* producer(void* arg) {
    long producer_id = (long)arg;

    for (int i = 0; i < 10; i++) {
        sem_wait(emptySlots); // 等待空闲位置
        sem_wait(mutex); // 进入临界区

        buffer[in] = producer_id;
        printf("生产者 %ld 生产了一个面包放在位置 %d\n", producer_id, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(mutex); // 离开临界区
        sem_post(fullSlots); // 增加已填充位置的数量
    }

    return NULL;
}

void* consumer(void* arg) {
    long consumer_id = (long)arg;

    for(int i = 0; i < 10; i++) {
        sem_wait(fullSlots); // 等待有面包的位置
        sem_wait(mutex); // 进入临界区

        printf("消费者 %ld 消费了生产者 %d 生产的面包，从位置 %d\n", consumer_id, buffer[out], out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(mutex); // 离开临界区
        sem_post(emptySlots); // 增加空闲位置的数量
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    // 创建和初始化信号量
    emptySlots = sem_open("emptySlots", O_CREAT, 0644, BUFFER_SIZE);
    fullSlots = sem_open("fullSlots", O_CREAT, 0644, 0);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);

    // 创建生产者和消费者线程
    for (long i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, (void*)i);
    }
    for (long i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void*)i);
    }

    // 等待线程结束（理论上这些线程不会结束）
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // 清理信号量
    sem_unlink("emptySlots");
    sem_unlink("fullSlots");
    sem_unlink("mutex");
    
    return 0;
}
