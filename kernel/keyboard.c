#include "type.h"
#include "const.h"
#include "protect.h"
#include "memory.h"
#include "string.h"
#include "proc.h"
#include "global.h"
#include "keyboard.h"
#include "keymap.h"

PRIVATE KB_INPUT    kb_in;

PUBLIC void keyboard_handler(int irq)
{
    u8 scan_code = in_byte(KB_DATA);
    if (kb_in.count < KB_IN_BYTES) {
        *(kb_in.p_head) = scan_code;
        kb_in.p_head++;
        if (kb_in.p_head == kb_in.buf + KB_IN_BYTES) {
            kb_in.p_head = kb_in.buf;
        }
        kb_in.count++;
    }
}

PUBLIC void init_keyboard()
{
    set_irq_handler(1, keyboard_handler);
    enable_irq(1);
    kb_in.count = 0;
    kb_in.p_head = kb_in.p_tail = kb_in.buf;
}

PUBLIC u8 keyboard_read()
{
    u8 scan_code;
    u8 res;
    char    output[2];
    if (kb_in.count > 0) {
        disable_int();
        scan_code = *(kb_in.p_tail);
        kb_in.p_tail++;
        if (kb_in.p_tail == kb_in.buf + KB_IN_BYTES) {
            kb_in.p_tail = kb_in.buf;
        }
        kb_in.count--;
        enable_int();
        if (scan_code == 28)
            return 28;
        if (scan_code == 0xE1) {
            return 0;
        }
        else if (scan_code == 0xE0) {
            return 0;
        }
        else {
            int make = (scan_code & FLAG_BREAK ? 0 : 1);
            if (make) {
                output[0] = keymap[(scan_code & 0x7F) * MAP_COLS];
                return output[0];
            }
            else return 0;
        }

    }
    else return 0;
}
