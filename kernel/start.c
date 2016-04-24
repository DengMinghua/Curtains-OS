#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "memory.h"
#include "proc.h"
#include "global.h"

PUBLIC  void*   memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC  void    disp_str(char * pszInfo);

PUBLIC  u8      gdt_ptr[6];
PUBLIC  DESCRIPTOR  gdt[GDT_SIZE];

PUBLIC void cstart()
{
    int flag = 1;
    print("\n\n\n\n\n\n\nKernel has been loaded\0",RED);
    memcpy(&gdt,
           (void*)(*((u32*)(&gdt_ptr[2]))),
           *((u16*)(&gdt_ptr[0])) + 1
        );
    u16* p_gdt_limit = (u16*)(&gdt_ptr[0]);
    u32* p_gdt_base  = (u32*)(&gdt_ptr[2]);
    *p_gdt_limit = GDT_SIZE * sizeof(DESCRIPTOR) - 1;
    *p_gdt_base  = (u32)&gdt;

    u16* p_idt_limit = (u16*)(&idt_ptr[0]);
    u32* p_idt_base  = (u32*)(&idt_ptr[2]);
    *p_idt_limit = IDT_SIZE * sizeof(GATE) - 1;
    *p_idt_base  = (u32)&idt;

    init_prot();

    print("\nPress Enter to Finsh Booting\0",WHITE);
     while (flag) {
        if (in_byte(KB_CMD) & 1) {
            u8 scan_code = in_byte(KB_DATA);
            if (scan_code == 28) flag = 0;
        }
    }
    clr();
}
