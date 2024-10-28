#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10 // 假设最多有10个内存块

// 内存块结构
typedef struct {
    int size;       // 内存块的大小
    int start;      // 内存块的起始地址
    int is_free;    // 是否是空闲块
} MemoryBlock;

MemoryBlock memory[MAX_BLOCKS]; // 模拟内存块

// 初始化内存块
void initialize_memory() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memory[i].size = (i + 1) * 100; // 随机大小
        memory[i].start = i * 100;
        memory[i].is_free = 1;
    }
}

// 最先匹配算法
int first_fit(int size) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size) {
            memory[i].is_free = 0;
            return memory[i].start;
        }
    }
    return -1; // 未找到合适的内存块
}

// 最佳匹配算法
int best_fit(int size) {
    int best_idx = -1;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size &&
            (best_idx == -1 || memory[i].size < memory[best_idx].size)) {
            best_idx = i;
        }
    }
    if (best_idx != -1) {
        memory[best_idx].is_free = 0;
        return memory[best_idx].start;
    }
    return -1;
}

// 最差匹配算法
int worst_fit(int size) {
    int worst_idx = -1;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size &&
            (worst_idx == -1 || memory[i].size > memory[worst_idx].size)) {
            worst_idx = i;
        }
    }
    if (worst_idx != -1) {
        memory[worst_idx].is_free = 0;
        return memory[worst_idx].start;
    }
    return -1;
}

int main() {
    initialize_memory(); // 初始化内存块

    // 测试分配
    printf("First Fit: %d\n", first_fit(250));
    printf("Best Fit: %d\n", best_fit(250));
    printf("Worst Fit: %d\n", worst_fit(250));

    return 0;
}
