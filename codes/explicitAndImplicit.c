#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    long id1, id2;
    // 显式系统调用
    syscall(1, 1, "Hello, world!\n", 14);
    id1 = syscall(SYS_getpid);
    printf("syscall(SYS_getpid) = %ld\n", id1);

    // 隐式系统调用
    write(1, "Hello, world!\n", 14);
    id2 = getpid();
    printf("getpid() = %ld\n", id2);

    return 0;
}