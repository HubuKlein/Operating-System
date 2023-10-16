#include <stdio.h>  
#include <unistd.h>
int main(int argc, char *argv[]) {  
   pid_t pid = fork(); // 创建子进程  
   if (pid == 0) { // 如果 pid 为 0，表示当前进程为子进程  
       printf("我是子进程，进程 ID 为：%d\n", getpid());  
   } else { // 如果 pid 不等于 0，表示当前进程为父进程  
       printf("我是父进程，进程 ID 为：%d\n", getpid());  
   }  
   return 0;  
}