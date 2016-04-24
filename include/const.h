#ifndef _CONST_H_
#define _CONST_H_

#define  EXTERN  extern

#define PUBLIC
#define PRIVATE static

#define GDT_SIZE    128
#define IDT_SIZE    256

#define PRIVILEGE_KRNL  0
#define PRIVILEGE_TASK  1
#define PRIVILEGE_USER  3

#define INT_M_CTL 0x20
#define INT_M_CTLMASK 0x21
#define INT_S_CTL 0xA0
#define INT_S_CTLMASK 0xA1
#define INT_VECTOR_IRQ0 0x20
#define INT_VECTOR_IRQ8 0x28

#define KB_DATA     0x60
#define KB_CMD      0x64

#define FLAG_BREAK  0x0080

#define MAX_TASKS_NUM 1

#define RPL_KRNL    SA_RPL0
#define RPL_TASK    SA_RPL1
#define RPL_USER    SA_RPL3

#define NR_IRQ 16
#define NR_SYS_CALL 1

#define TIMER0         0x40
#define TIMER_MODE     0x43
#define RATE_GENERATOR 0x34


#define TIMER_FREQ     1193182L
#define HZ             100

#endif /* _CONST_H_ */
