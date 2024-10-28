#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER 5
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10

sem_t empty;
sem_t full;
sem_t mutex;

int buffer[MAX_BUFFER];
int in = 0;
int out = 0;

void* producer(void* arg) {
    int producer_id = *((int*)arg);

    for (int i = 0; i < 10; i++) {
        sem_wait(&empty); // 等待空闲位置
        sem_wait(&mutex); // 进入临界区

        buffer[in] = producer_id;
        printf("生产者 %d 生产了一个面包放在位置 %d\n", producer_id, in);
        in = (in + 1) % MAX_BUFFER;

        sem_post(&mutex); // 离开临界区
        sem_post(&full); // 增加已填充位置的数量
    }

    return NULL;
}

void* consumer(void* arg) {
    int consumer_id = *((int*)arg);

    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // 等待有面包的位置
        sem_wait(&mutex); // 进入临界区

        printf("消费者 %d 消费了生产者 %d 生产的面包，从位置 %d\n", consumer_id, buffer[out], out);
        out = (out + 1) % MAX_BUFFER;

        sem_post(&mutex); // 离开临界区
        sem_post(&empty); // 增加空闲位置的数量
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];

    // 初始化信号量
    sem_init(&empty, 0, MAX_BUFFER);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // 创建生产者和消费者线程
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i;
        pthread_create(&producers[i], NULL, producer, (void*)&producer_ids[i]);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i;
        pthread_create(&consumers[i], NULL, consumer, (void*)&consumer_ids[i]);
    }

    // 等待线程结束（这些线程不会自然结束，所以这里实际上是无限等待）
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // 清理信号量
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
