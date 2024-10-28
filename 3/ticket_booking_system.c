#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TOTAL_TICKETS 100
#define NUM_THREADS 200

int tickets = TOTAL_TICKETS;
pthread_mutex_t ticketMutex;

void* ticket_booking(void* arg) {
    long thread_id = (long)arg;

    // 尝试抢票
    pthread_mutex_lock(&ticketMutex);
    if (tickets > 0) {
        printf("线程%ld抢走了第%d号门票。\n", thread_id, tickets);
        tickets--;
    }
    pthread_mutex_unlock(&ticketMutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // 初始化互斥锁
    pthread_mutex_init(&ticketMutex, NULL);

    // 创建线程
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, ticket_booking, (void*)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        usleep(1000);
    }

    // 等待线程结束
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // 清理互斥锁
    pthread_mutex_destroy(&ticketMutex);

    return 0;
}
