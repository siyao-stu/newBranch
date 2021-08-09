#include <stdio.h>

/**
 * 3. （选做）实现库函数strncpy
 *    将src指向的字符串（包括空终止字符'\0'）最多复制n个字节到dest指向的缓冲区。
 *    即当src的长度大于n时，则只复制src中前n个字节到dest指向的缓冲区。
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    for (; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}

