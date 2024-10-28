#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/**
 * @brief 程序演示了动态内存分配和进程创建的过程。
 * 
 * 程序首先打印当前进程的PID，然后创建了四个指针变量a、b、c和d。
 * 接下来，程序通过malloc函数分配了大量内存给a、b和c，并打印了相应的提示信息。
 * 然后，程序通过free函数释放了指针b所指向的内存，并打印了相应的提示信息。
 * 最后，程序通过malloc函数又分配了更大的内存给指针d，并打印了相应的提示信息。
 * 
 * @return 返回0表示程序执行成功。
 */
int main()
{
    printf("pid = %d\n", getpid());

    int *a, *b, *c, *d;

    printf("program begins:\n");
    getchar();

    a = (int *)malloc(pow(2, 27) * sizeof(int));
    b = (int *)malloc(pow(2, 27) * sizeof(int));
    c = (int *)malloc(pow(2, 27) * sizeof(int));
    printf("Memory of a, b, c are already created!\n");
    printf("Type to free b:\n");
    getchar();
    free(b);
    printf("Memory of b is already freed!\n");
    printf("Type to create new process d:\n");
    getchar();

    d = (int *)malloc(pow(2, 28) * sizeof(int));
    printf("Memory of d is already created!\n");
    getchar();
    
    return 0;
}