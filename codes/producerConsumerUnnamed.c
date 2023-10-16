/*
 * This program demonstrates the producer-consumer problem using unnamed semaphores in C.
 * The program creates two threads, one for producing items and another for consuming them.
 * The shared buffer has a fixed size of NBUFF and is protected by three semaphores: mutex, empty and full.
 * The mutex semaphore ensures mutual exclusion while accessing the buffer.
 * The empty semaphore keeps track of the number of empty slots in the buffer.
 * The full semaphore keeps track of the number of filled slots in the buffer.
 * The producer thread waits on the empty semaphore and acquires the mutex semaphore before producing an item.
 * The consumer thread waits on the full semaphore and acquires the mutex semaphore before consuming an item.
 * After producing or consuming an item, the corresponding semaphore is incremented and the mutex semaphore is released.
 * The program uses POSIX semaphores and threads.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NBUFF 10 // size of the shared buffer

int nitems = 2; // number of items to produce and consume

struct {
    int buff[NBUFF]; // shared buffer
    int count; // number of items in the buffer
    sem_t mutex, empty, full; // semaphores for mutual exclusion and synchronization
} shared;

void *produce(void *);
void *consume(void *);

int main(int argc, char *argv[])
{
    pthread_t tid_produce, tid_consume;

    // initialize the semaphores
    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.empty, 0, NBUFF);
    sem_init(&shared.full, 0, 0);

    // create the producer and consumer threads
    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_consume, NULL, consume, NULL);

    // wait for the threads to finish
    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    // destroy the semaphores
    sem_destroy(&shared.mutex);
    sem_destroy(&shared.empty);
    sem_destroy(&shared.full);

    return 0;
}

// producer thread function
void *produce(void *arg)
{
    int i;
    for (i = 0; i < nitems; i++) {
        sem_wait(&shared.empty); // wait for an empty slot in the buffer
        sem_wait(&shared.mutex); // acquire the mutex semaphore
        // shared.buff[i % NBUFF] = i; // produce an item and store it in the buffer
        shared.count++; // increment the number of items in the buffer
        printf("produce 1, %d remaining\n", shared.count);
        sleep(1); // simulate some work
        sem_post(&shared.mutex); // release the mutex semaphore
        sem_post(&shared.full); // signal that a slot in the buffer is filled
    }
    return NULL;
}

// consumer thread function
void *consume(void *arg)
{
    int i;
    for (i = 0; i < nitems; i++) {
        sem_wait(&shared.full); // wait for a filled slot in the buffer
        sem_wait(&shared.mutex); // acquire the mutex semaphore
        // if (shared.buff[i % NBUFF] != i) // consume an item from the buffer
        //     printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
        shared.count--; // decrement the number of items in the buffer
        printf("consume 1, %d remaining\n", shared.count);
        sleep(1); // simulate some work
        sem_post(&shared.mutex); // release the mutex semaphore
        sem_post(&shared.empty); // signal that a slot in the buffer is empty
    }
    return NULL;
}