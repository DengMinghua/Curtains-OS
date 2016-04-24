void TestA();
void TestB();
typedef void(*task_f) ();
typedef struct register_list{
    int gs;
    int fs;
    int es;
    int ds;
    int edi;
    int esi;
    int ebp;
    int kernel_esp;
    int ebx;
    int edx;
    int ecx;
    int eax;
    int retaddr;
    int eip;
    int cs;
    int eflags;
    int esp;
    int ss;
}REG_LIST;

typedef struct proc_block{
    REG_LIST regs;

    short ldt_sel;
    DESCRIPTOR ldts[LDT_SIZE];
    int pid;

    char name[16];
}PROC;

typedef struct task {
    task_f initial_eip;
    int stacksize;
    char name[32];
}TASK;


#define NR_TASKS    2

#define STACK_SIZE_TESTA    0x8000
#define STACK_SIZE_TESTB    0x8000

#define STACK_SIZE_TOTAL    (STACK_SIZE_TESTA + STACK_SIZE_TESTB)



