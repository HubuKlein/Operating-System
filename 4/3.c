#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 640 // 假设内存大小为640KB

typedef struct SubAreaNode {
    int address; // 分区起始地址
    int size;    // 分区大小
    int state;   // 分区状态(0空闲,1占用)
    int taskNo;  // 记录作业号
    struct SubAreaNode *prior; // 分区的前向指针
    struct SubAreaNode *next;  // 分区的后继指针
} SubAreaNode;

SubAreaNode *head = NULL; // 定义全局的头指针

// 初始化内存分区链表
void initializeMemory() {
    head = (SubAreaNode *)malloc(sizeof(SubAreaNode));
    head->address = 0;
    head->size = MEMORY_SIZE;
    head->state = 0; // 初始状态为空闲
    head->taskNo = 0;
    head->prior = head->next = NULL;
}

// 显示内存分区
void displayMemory() {
    SubAreaNode *current = head;
    printf("当前内存分区情况:\n");
    while (current) {
        printf("地址: %d, 大小: %dKB, 状态: %s, 作业号: %d\n",
               current->address, current->size, current->state == 0 ? "空闲" : "占用",
               current->taskNo);
        current = current->next;
    }
}

// 查找合适的分区（首次适配策略）
SubAreaNode *findFirstFit(int size) {
    SubAreaNode *current = head;
    while (current) {
        if (current->state == 0 && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL; // 没有找到合适的分区
}

// 查找合适的分区（最佳适配策略）
SubAreaNode *findBestFit(int size) {
    SubAreaNode *current = head;
    SubAreaNode *best = NULL;
    while (current) {
        if (current->state == 0 && current->size >= size) {
            if (best == NULL || current->size < best->size) {
                best = current;
            }
        }
        current = current->next;
    }
    return best;
}

// 查找合适的分区（最差适配策略）
SubAreaNode *findWorstFit(int size) {
    SubAreaNode *current = head;
    SubAreaNode *worst = NULL;
    while (current) {
        if (current->state == 0 && current->size >= size) {
            if (worst == NULL || current->size > worst->size) {
                worst = current;
            }
        }
        current = current->next;
    }
    return worst;
}

// 分配内存
int allocate(SubAreaNode *(*findFit)(int), int taskNo, int size) {
    SubAreaNode *fit = findFit(size);
    if (!fit) {
        printf("内存分配失败: 没有足够的空间为作业%d分配%dKB内存。\n", taskNo, size);
        return -1; // 内存分配失败
    }
    // 判断是否需要分割
    if (fit->size > size) {
        SubAreaNode *newNode = (SubAreaNode *)malloc(sizeof(SubAreaNode));
        newNode->address = fit->address + size;
        newNode->size = fit->size - size;
        newNode->state = 0;
        newNode->taskNo = 0;
        newNode->next = fit->next;
        newNode->prior = fit;
        if (fit->next) {
            fit->next->prior = newNode;
        }
        fit->next = newNode;
        fit->size = size;
    }
    // 分配内存
    fit->state = 1;
    fit->taskNo = taskNo;
    printf("已为作业%d分配%dKB内存。\n", taskNo, size);
    return 0; // 内存分配成功
}

// 回收内存
int deallocate(int taskNo) {
    SubAreaNode *current = head;
    while (current) {
        if (current->state == 1 && current->taskNo == taskNo) {
            current->state = 0;
            current->taskNo = 0;

            // 合并与前一个空闲块
            if (current->prior && current->prior->state == 0) {
                current->prior->size += current->size;
                current->prior->next = current->next;
                if (current->next) {
                    current->next->prior = current->prior;
                }
                free(current);
                current = current->prior;
            }
            // 合并与后一个空闲块
            if (current->next && current->next->state == 0) {
                current->size += current->next->size;
                SubAreaNode *temp = current->next;
                current->next = temp->next;
                if (temp->next) {
                    temp->next->prior = current;
                }
                free(temp);
            }
            printf("已释放作业%d占用的内存。\n", taskNo);
            return 0; // 内存回收成功
        }
        current = current->next;
    }
    printf("内存回收失败: 未找到作业%d的内存分区。\n", taskNo);
    return -1; // 内存回收失败
}

int main() {
    initializeMemory();
    displayMemory();

    allocate(findWorstFit, 1, 130);
    allocate(findWorstFit, 2, 60);
    allocate(findWorstFit, 3, 100);
    deallocate(2);
    allocate(findWorstFit, 4, 200);
    deallocate(3);
    deallocate(1);
    allocate(findWorstFit, 5, 140);
    allocate(findWorstFit, 6, 60);
    allocate(findWorstFit, 7, 50);
    deallocate(6);
    
    displayMemory();
    
    return 0;
}