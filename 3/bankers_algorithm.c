// 只输出一种安全序列

#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

bool checkSafety(int processes[], int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES]) {
    bool finish[NUM_PROCESSES] = {false};
    int safeSequence[NUM_PROCESSES];

    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++) {
            if (finish[p] == false) {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == NUM_RESOURCES) {
                    for (int k = 0; k < NUM_RESOURCES; k++)
                        work[k] += allocation[p][k];

                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (found == false) {
            printf("系统不处于安全状态。\n");
            return false;
        }
    }

    printf("系统处于安全状态。\n安全序列是: ");
    for (int i = 0; i < NUM_PROCESSES; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return true;
}

int main() {
    // 进程标识符
    int processes[NUM_PROCESSES] = {0, 1, 2, 3, 4};

    // 可用资源数组
    int available[NUM_RESOURCES] = {2, 3, 3};

    // 最大需求矩阵
    int max[NUM_PROCESSES][NUM_RESOURCES] = {{5, 5, 9}, {5, 3, 6}, {4, 0, 11}, {4, 2, 5}, {4, 2, 4}};

    // 已分配资源矩阵
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {{2, 1, 2}, {4, 0, 2}, {4, 0, 5}, {2, 0, 4}, {3, 1, 4}};

    // 需求矩阵
    int need[NUM_PROCESSES][NUM_RESOURCES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // 检查系统是否处于安全状态
    bool safe = checkSafety(processes, available, max, allocation, need);

    return 0;
}
