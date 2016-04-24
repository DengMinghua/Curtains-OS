#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "memory.h"
#include "proc.h"
#include "global.h"

int k_reenter;

extern disp_pos;

void restart();
void TestA() {
    while (1) {
        print("A", RED);
        print(" . ", WHITE);
        delay(1);
    }
}

void TestB() {
    char swing[4] = {'|','/','-','\\'};
    int i = -1;
    int disp_back;
    while (1) {
        disp_back = disp_pos;
        i = (i + 1) % 4;
        if (i % 2 == 0)
        putchar_kept(swing[i],WHITE,79,1);
        else
        putchar_kept(swing[i],RED,79,1);
        disp_pos = disp_back;
        delay(20);
    }
}

PUBLIC int kernel_main() {

    //init_clock();
    init_keyboard();


    TASK* task_ptr = task_table;
    PROC * proc_ptr = proc_table;
    char* p_task_stack = task_stack + STACK_SIZE_TOTAL;
    u16 selector_ldt = SELECTOR_LDT_FIRST;

    for (int i = 0; i < NR_TASKS; i++) {
        for (int j = 0; j < 16; j++) {
            proc_ptr->name[j] = task_ptr->name[j];
        }
        proc_ptr->pid = i;
        proc_ptr->ldt_sel = selector_ldt;
        memcpy(&proc_ptr->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(DESCRIPTOR));
        proc_ptr->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5;
        memcpy(&proc_ptr->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(DESCRIPTOR));
        proc_ptr->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;

        proc_ptr->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        proc_ptr->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        proc_ptr->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        proc_ptr->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        proc_ptr->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | RPL_TASK;
        proc_ptr->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | RPL_TASK;

        proc_ptr->regs.eip = (u32)task_ptr->initial_eip;
        proc_ptr->regs.esp = (u32)p_task_stack;
        proc_ptr->regs.eflags = 0x1202;

        p_task_stack -= task_ptr->stacksize;
        proc_ptr++;
        task_ptr++;
        selector_ldt += 1 << 3;
    }
    k_reenter = 0;

    p_proc_ready    = proc_table;

    set_irq_handler(0, clock_handler);
    enable_irq(0);

    restart();

    while (1) {
    }
}
