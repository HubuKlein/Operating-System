#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#define NBUFF 10 // size of the shared buffer

int nitems = 2; // number of items to produce and consume

struct {
    int buff[NBUFF]; // shared buffer
    int count; // number of items in the buffer
    sem_t *mutex, *empty, *full; // semaphores for mutual exclusion and synchronization
} shared;

void *produce(void *);
void *consume(void *);

int main(int argc, char *argv[])
{
    pthread_t tid_produce, tid_consume;

    // initialize semaphores
    shared.mutex = sem_open("/mutex", O_CREAT | O_EXCL, 0666, 1);
    shared.empty = sem_open("/empty", O_CREAT | O_EXCL, 0666, NBUFF);
    shared.full = sem_open("/full", O_CREAT | O_EXCL, 0666, 0);

    // create producer and consumer threads
    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_consume, NULL, consume, NULL);

    // wait for threads to finish
    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    // close and unlink semaphores
    sem_close(shared.mutex);
    sem_close(shared.empty);
    sem_close(shared.full);
    sem_unlink("/mutex");
    sem_unlink("/empty");
    sem_unlink("/full");

    return 0;
}

void *produce(void *arg)
{
    int i, item;

    for (i = 0; i < nitems; i++) {
        // wait for an empty slot
        sem_wait(shared.empty);

        // acquire the mutex lock
        sem_wait(shared.mutex);

        // produce an item
        item = i;
        shared.buff[shared.count++] = item;
        printf("Produced item %d, count = %d\n", item, shared.count);

        // release the mutex lock
        sem_post(shared.mutex);

        // signal that a slot in the buffer is filled
        sem_post(shared.full);

        // simulate some work
        sleep(1);
    }

    return NULL;
}

void *consume(void *arg)
{
    int i, item;

    for (i = 0; i < nitems; i++) {
        // wait for a filled slot
        sem_wait(shared.full);

        // acquire the mutex lock
        sem_wait(shared.mutex);

        // consume an item
        item = shared.buff[--shared.count];
        printf("Consumed item %d, count = %d\n", item, shared.count);

        // release the mutex lock
        sem_post(shared.mutex);

        // signal that an empty slot in the buffer is available
        sem_post(shared.empty);

        // simulate some work
        sleep(1);
    }

    return NULL;
}