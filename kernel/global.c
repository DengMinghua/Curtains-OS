#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "memory.h"
#include "proc.h"
#include "global.h"
#include "string.h"

PUBLIC PROC proc_table[MAX_TASKS_NUM];

PUBLIC char task_stack[STACK_SIZE_TOTAL];

PUBLIC  TASK task_table[NR_TASKS] =
{
    {tty, STACK_SIZE_TESTA, "tty"},
    {TestB, STACK_SIZE_TESTB, "TestB"}
};

PUBLIC  irq_handler irq_table[NR_IRQ];

PUBLIC  system_call sys_call_table[NR_SYS_CALL] = {
    sys_get_time
};

