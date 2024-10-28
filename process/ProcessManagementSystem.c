#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

int createProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("创建进程失败");
        return -1;
    }
    if (pid == 0) {
        // 子进程
        printf("子进程创建成功，PID: %d\n", getpid());
        exit(0);
    } else {
        // 父进程
        printf("父进程PID: %d，创建子进程PID: %d\n", getpid(), pid);
        wait(NULL);
        return pid;
    }
}

void switchProcess(pid_t pid) {
    if (kill(pid, SIGSTOP) < 0) {
        perror("进程暂停失败");
    } else {
        printf("进程PID %d 已暂停\n", pid);
    }
}

void resumeProcess(pid_t pid) {
    if (kill(pid, SIGCONT) < 0) {
        perror("进程恢复失败");
    } else {
        printf("进程PID %d 已恢复\n", pid);
    }
}

void killProcess(pid_t pid) {
    if (kill(pid, SIGKILL) < 0) {
        perror("进程终止失败");
    } else {
        printf("进程PID %d 已终止\n", pid);
    }
}

void listProcesses() {
    system("ps -au");
}

int main() {
    int choice;
    pid_t pid;

    while (1) {
        sleep(0.5);
        printf("\n1. 创建新进程\n");
        printf("2. 列出所有运行中的进程\n");
        printf("3. 终止进程\n");
        printf("4. 切换进程\n");
        printf("5. 唤醒进程\n");
        printf("6. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                pid = createProcess();
                break;
            case 2:
                listProcesses();
                break;
            case 3:
                printf("请输入要终止的进程PID: ");
                scanf("%d", &pid);
                killProcess(pid);
                break;
            case 4:
                printf("请输入要切换的进程PID: ");
                scanf("%d", &pid);
                switchProcess(pid);
                break;
            case 5:
                printf("请输入要唤醒的进程PID: ");
                scanf("%d", &pid);
                resumeProcess(pid);
                break;
            case 6:
                printf("退出\n");
                exit(0);
                break;
            default:
                printf("无效的选择\n");
        }
    }
    return 0;
}
