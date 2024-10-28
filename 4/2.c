#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // 要复制的字符串
    const char *source = "xieshiqiang";
    
    // 计算需要分配的内存大小（包括空终止符）
    size_t size = strlen(source) + 1;
    
    // 为字符串分配内存
    char *dest = (char *)malloc(size);
    
    // 检查内存是否成功分配
    if (dest == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    
    // 将字符串复制到分配的内存
    strcpy(dest, source);
    
    // 显示字符串
    printf("%s\n", dest);
    
    // 释放内存
    free(dest);
    
    return 0;
}