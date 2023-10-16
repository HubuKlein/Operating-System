#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buf[12];
    if (pipe(fd) < 0)
    {
        printf("pipe error\n");
        return -1;
    }
    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        return -1;
    }
    else if (pid > 0)
    {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buf, 12);
        printf("%s", buf);
    }
    return 0;
}