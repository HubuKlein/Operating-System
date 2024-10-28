#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("The location of code: %p\n", (void *)main);
    printf("The location of heap: %p\n", (void *)malloc(1));
    int x = 1;
    printf("The location of stack: %p\n", &x);
    int y = 10;
    printf("The location of y in stack: %p\n", &y);
    sleep(30);
    
    return 0;
}