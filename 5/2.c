#include <stdio.h>
#include <stdbool.h>

#define PAGES_REQUESTED 12  // 请求的页面数
#define FRAMES 3  // 帧数

int pages[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};  // 页面请求序列
int frame[FRAMES];  // 帧数组

// 初始化帧数组
void initialize() {
    for (int i = 0; i < FRAMES; i++) {
        frame[i] = -1;
    }
}

// 检查页面是否在帧中
bool isPageInFrame(int page) {
    for (int i = 0; i < FRAMES; i++) {
        if (frame[i] == page) {
            return true;
        }
    }
    return false;
}

// 打印帧内容
void printFrames() {
    for (int i = 0; i < FRAMES; i++) {
        if (frame[i] != -1) {
            printf("%d ", frame[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

// FIFO页面替换算法
void fifo() {
    printf("FIFO Page Replacement\n");
    initialize();
    int pointer = 0;  // 指针，用于指示下一个要替换的帧
    int pageFaults = 0;  // 页面错误数

    for (int i = 0; i < PAGES_REQUESTED; i++) {
        if (!isPageInFrame(pages[i])) {
            frame[pointer] = pages[i];
            pointer = (pointer + 1) % FRAMES;
            pageFaults++;
            printFrames();
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// LRU页面替换算法
void lru() {
    printf("LRU Page Replacement\n");
    initialize();
    int recentlyUsed[FRAMES] = {0};  // 最近使用的页面
    int time = 0;  // 时间
    int pageFaults = 0;  // 页面错误数

    for (int i = 0; i < PAGES_REQUESTED; i++) {
        time++;
        if (!isPageInFrame(pages[i])) {
            int leastRecent = time, replaceIndex = 0;
            for (int j = 0; j < FRAMES; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j;
                    break;
                } else if (recentlyUsed[j] < leastRecent) {
                    leastRecent = recentlyUsed[j];
                    replaceIndex = j;
                }
            }
            frame[replaceIndex] = pages[i];
            pageFaults++;
            printFrames();
        }
        for (int j = 0; j < FRAMES; j++) {
            if (frame[j] == pages[i]) {
                recentlyUsed[j] = time;
                break;
            }
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// 时钟页面替换算法
void clock() {
    printf("Clock Page Replacement\n");
    initialize();
    bool referenceBit[FRAMES] = {false};  // 引用位
    int pointer = 0;  // 指针，用于指示下一个要替换的帧
    int pageFaults = 0;  // 页面错误数

    for (int i = 0; i < PAGES_REQUESTED; i++) {
        bool pagePlaced = false;
        while (!pagePlaced) {
            if (!isPageInFrame(pages[i])) {
                while (referenceBit[pointer]) {
                    referenceBit[pointer] = false;
                    pointer = (pointer + 1) % FRAMES;
                }
                frame[pointer] = pages[i];
                referenceBit[pointer] = true;
                pointer = (pointer + 1) % FRAMES;
                pageFaults++;
                pagePlaced = true;
                printFrames();
            } else {
                for (int j = 0; j < FRAMES; j++) {
                    if (frame[j] == pages[i]) {
                        referenceBit[j] = true;
                        break;
                    }
                }
                pagePlaced = true;
            }
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// 主函数
int main() {
    fifo();  // 执行FIFO页面替换算法
    printf("\n");
    lru();  // 执行LRU页面替换算法
    printf("\n");
    clock();  // 执行时钟页面替换算法

    return 0;
}