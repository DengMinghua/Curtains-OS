#ifdef  GLOBAL_VARIABLES_HERE
#undef  EXTERN
#define EXTERN
#endif

extern  PROC       proc_table[];
extern  char        task_stack[];
extern  TASK        task_table[];
extern  irq_handler irq_table[];

EXTERN  TSS     tss;
EXTERN  PROC*    p_proc_ready;



EXTERN  int     disp_pos;
EXTERN  u8      gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN  DESCRIPTOR  gdt[GDT_SIZE];
EXTERN  u8      idt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN  GATE        idt[IDT_SIZE];

PUBLIC void clock_handler(int irq);

int k_reenter;

