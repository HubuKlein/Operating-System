#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // 包含wait()函数的头文件

int main()
{
    printf("hello, world (pid: %d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid: %d)\n", (int)getpid());

        // 使用execlp运行ps命令
        execlp("ps", "ps", "aux", NULL); // "ps aux"显示所有运行中的进程

        // 如果execlp成功，下面的代码不会被执行
        printf("This line should not be printed\n");
    } else {
        int wc = wait(NULL); // 等待子进程结束
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int)getpid());
    }
}