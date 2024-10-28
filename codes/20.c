#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
int main()
{
    int r=fork();
    if(r<0) {
    fprintf(stderr,"fork failed \n");
    exit(1);
    } else if(r==0) {
        printf("I am child (pid:%d)\n",(int)getpid());
    } else {
        int wc = wait(NULL);
        printf("I am parent of %d (pid:%d)\n",wc,(int)getpid());
    }
    exit(0);
}