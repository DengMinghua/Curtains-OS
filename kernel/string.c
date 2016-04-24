#include "string.h"
void print(char* str, int color) {
    for (char* ch = str; (*ch) != '\0'; ch++) {
        putchar(*ch, color, 0, 0);
    }
}

void print_fixed(char* str, int color, int len,int align) {
    char reserved[256];
    int i;
    for (i = 0;i < 256; i++) reserved[i] = 0;
    for (i = 0; i < len; i++) {
        reserved[i] = str[i];
        if (str[i] == 0) len--;
    }
    print(reserved,color);
    if (align > len)
        for (i = len; i < align; i++) print(" ",WHITE);
}

void clr() {
    putchar(' ', WHITE, 1, 0);
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 79; j++) {
            putchar(' ', WHITE, 0, 0);
        }
    }
    putchar(' ', WHITE, 1, 0);
}

char * itoa(char * str, int num) {
    char *  p = str;
    char    ch;
    int i;
    int flag = 0;

    if (num == 0) {
        *p = '0';
        p++;
    }
    else {
        while (num != 0) {
            *p = '0' + num % 10;
            p++;
            num /= 10;
        }
    }
    char * q;
    *p = 0;
    p--;
    for (q = str; p > q;  q++, p--) {
        ch = *q;
        *q = *p;
        *p = ch;
    }
    ++q;
    q = 0;

    return str;
}


void print_int(int input, int color)
{
    char output[16];
    itoa(output, input);
    print(output, color);
}

void delay(int time) {
    for (int k = 0; k < time; k++)
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10000; j++) {}
}


