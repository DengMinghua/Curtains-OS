#ifndef _STRING_H_
#define _STRING_H_

#define  WHITE 15
#define  YELLOW 14
#define  RED 4
#define  BLUE 1
#define  LIGHTRED 12
void   disp_str(char * pszInfo);

void putchar(int ch, int color, int posx, int posy);

void print(char* str, int color);

void clr();

char * itoa(char * str, int num);

void print_int(int input,int color);

void print_fixed(char* str, int color, int len,int align);
void delay(int time);
#endif
