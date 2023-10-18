#include <stdio.h>
#include <stdbool.h>

#define N 5 // Number of processes
#define M 3 // Number of resource types

int max[N][M] = { // Maximum demand of each process
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[N][M] = { // Currently allocated resources to each process
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int available[M] = {3, 3, 2}; // Currently available resources

bool needToFinish[N]; // To mark the processes that need to be finished

bool isSafe() {
    int work[M];
    for (int i = 0; i < M; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < N; i++) {
        needToFinish[i] = true;
    }

    while (true) {
        bool found = false;
        for (int p = 0; p < N; p++) {
            if (needToFinish[p]) {
                bool enoughResources = true;
                for (int r = 0; r < M; r++) {
                    if (max[p][r] - allocation[p][r] > work[r]) {
                        enoughResources = false;
                        break;
                    }
                }
                if (enoughResources) {
                    for (int r = 0; r < M; r++) {
                        work[r] += allocation[p][r];
                    }
                    needToFinish[p] = false;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int p = 0; p < N; p++) {
        if (needToFinish[p]) {
            return false;
        }
    }
    return true;
}

int main() {
    if (isSafe()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    return 0;
}
