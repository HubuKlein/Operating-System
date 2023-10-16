#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10 // 最大参数数
#define MAX_LINE 1024 // 最大命令行长度

// 解析命令行参数
void parse_args(char *line, char **args, int *argc) {
    *argc = 0;
    char *token = strtok(line, " ");
    while (token != NULL && *argc < MAX_ARGS) {
        args[(*argc)++] = token;
        token = strtok(NULL, " ");
    }
    args[*argc] = NULL;
}

// 执行命令
void execute(char **args, int argc) {
    if (argc == 0) {
        return;
    }
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    pid_t pid = fork();
    if (pid == 0) {
        // 子进程
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        // 父进程
        waitpid(pid, NULL, 0);
    } else {
        perror("fork");
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    int argc;
    while (1) {
        printf("> ");
        fgets(line, MAX_LINE, stdin);
        line[strlen(line) - 1] = '\0'; // 去掉换行符
        parse_args(line, args, &argc);
        execute(args, argc);
        argc = 0;
    }
    return 0;
}