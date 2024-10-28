#include <stdio.h>

int main() {
    unsigned long long counter = 0;

    while (1) {  // 无限循环
        counter++;  // 增加计数器

        // 每隔一定次数输出一次信息，以便观察程序是否在持续运行
        if (counter % 1000000000 == 0) {
            printf("程序正在运行，计数器值：%llu\n", counter);
        }
    }

    return 0;
}
