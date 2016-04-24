#include "type.h"
#include "const.h"
#include "protect.h"
#include "memory.h"
#include "string.h"
#include "proc.h"
#include "global.h"

PUBLIC void default_irq_handler(int irq)
{
    return;
}

PUBLIC void init_8259A()
{
    out_byte(INT_M_CTL, 0x11);

    out_byte(INT_S_CTL, 0x11);

    out_byte(INT_M_CTLMASK, INT_VECTOR_IRQ0);

    out_byte(INT_S_CTLMASK, INT_VECTOR_IRQ8);

    out_byte(INT_M_CTLMASK, 0x4);

    out_byte(INT_S_CTLMASK, 0x2);

    out_byte(INT_M_CTLMASK, 0x1);

    out_byte(INT_S_CTLMASK, 0x1);

    out_byte(INT_M_CTLMASK, 0xFD);

    out_byte(INT_S_CTLMASK, 0xFF);

    int i;
    for (i = 0; i < NR_IRQ; i++)
        irq_table[i] = default_irq_handler;
}



PUBLIC void set_irq_handler(int irq, irq_handler handler){
    disable_irq(irq);
    irq_table[irq] = handler;
}

