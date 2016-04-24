#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "global.h"
#include "string.h"
#include "memory.h"

PUBLIC void clock_handler(int irq) {
    if (k_reenter != 0) {
        return;
    }
    if (p_proc_ready + 1 >= proc_table + NR_TASKS)
        p_proc_ready = proc_table;
    else p_proc_ready++;
}

PUBLIC void init_clock()
{
    out_byte(TIMER_MODE, RATE_GENERATOR);
    out_byte(TIMER0, (u8)(TIMER_FREQ / HZ));
    out_byte(TIMER0, (u8)((TIMER_FREQ / HZ) >> 8));

    set_irq_handler(0, clock_handler);
    enable_irq(0);
}
