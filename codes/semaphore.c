/**
 * @file semaphore.c
 * @brief This program demonstrates the use of semaphores in inter-process communication.
 * 
 * The program creates a semaphore and forks a child process. The parent and child processes
 * take turns printing their process ID and a counter to the console, with the semaphore
 * ensuring that only one process can access the shared resource at a time.
 * 
 * @note This program requires the <stdio.h>, <stdlib.h>, <unistd.h>, <semaphore.h>, <pthread.h>,
 * <sys/types.h>, <sys/wait.h>, and <sys/ipc.h> header files.
 * 
 * @author k13in
 * @date 2023.10.12
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int pid;
    sem_t *sem;
    const char sem_name[] = "mysem";

    pid = fork();

    if (pid < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        sem = sem_open(sem_name, O_CREAT, 0644, 1);
        if (sem == SEM_FAILED) {
            printf("sem_open error\n");
            sem_unlink(sem_name);
            exit(-1);
        }
        sem_wait(sem);
        for (int i = 0; i < 3; i++) {
            printf("child process run: %d\n", i);
            sleep(1);
        }
        sem_post(sem);
    } else {
        sem = sem_open(sem_name, O_CREAT, 0644, 1);
        if (sem == SEM_FAILED) {
            printf("sem_open error\n");
            sem_unlink(sem_name);
            exit(-1);
        }
        sem_wait(sem);
        for (int i = 0; i < 3; i++) {
            printf("parent process run: %d\n", i);
            sleep(1);
        }
        sem_post(sem);
        wait(NULL);
        sem_close(sem);
        sem_unlink(sem_name);
    }

    return 0;
}