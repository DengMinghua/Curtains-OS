%include "sconst.inc"

global string
extern  cstart
extern  exception_handler
extern  keyboard_handler
extern  gdt_ptr
extern  idt_ptr
extern  shell
extern  kernel_main
extern  p_proc_ready
extern  tss
extern  k_reenter
extern  putchar
extern  disp_str
extern  clock_handler
extern  int_33
extern  int_34
extern  int_35
extern  int_36

extern  sys_call_table

extern irq_table

bits 32

[SECTION .data]
clock_int_msg       db  "^", 0
bpb_ptr     dd 7c00h

[SECTION .bss]
StackSpace      resb    2 * 1024
StackTop:

[section .text]

global _start

global  divide_error
global  single_step_exception
global  nmi
global  breakpoint_exception
global  overflow
global  bounds_check
global  inval_opcode
global  copr_not_available
global  double_fault
global  copr_seg_overrun
global  inval_tss
global  segment_not_present
global  stack_exception
global  general_protection
global  page_fault
global  copr_error
global  restart
global  bpb_ptr

global  hwint00
global  hwint01
global  hwint02
global  hwint03
global  hwint04
global  hwint05
global  hwint06
global  hwint07
global  hwint08
global  hwint09
global  hwint10
global  hwint11
global  hwint12
global  hwint13
global  hwint14
global  hwint15

global sys_call_33
global sys_call_34
global sys_call_35
global sys_call_36


%macro hwint_master 1
    call save
    in al, 0x21
    or al, (1 << %1)
    out 0x21, al
    mov al, EOI
    out 0x20, al
    sti
    push %1
    call [irq_table + 4 * %1]
    pop ecx
    cli
    in al, 0x21
    and al, ~(1 << %1)
    out 0x21, al
    ret
%endmacro

_start:

    mov esp, StackTop

    sgdt    [gdt_ptr]
    call    cstart
    lgdt    [gdt_ptr]

    lidt    [idt_ptr]

    jmp SELECTOR_KERNEL_CS:csinit
csinit:

    xor eax, eax
    mov ax, SELECTOR_TSS
    ltr ax
    jmp kernel_main

%macro  hwint_default 1
        iretd
%endmacro
; ---------------------------------

sys_call_33:
    call save

    sti

    call int_33

    cli

    ret
sys_call_34:
    call save

    sti

    call int_33

    cli

    ret
sys_call_35:
    call save

    sti

    call int_33

    cli

    ret
sys_call_36:
    call save

    sti

    call int_33

    cli

    ret

ALIGN   16
hwint00:                ; Interrupt routine for irq 0 (the clock).
        hwint_master 0
ALIGN   16
hwint01:                ; Interrupt routine for irq 1 (keyboard)
        hwint_master 1

ALIGN   16
hwint02:                ; Interrupt routine for irq 2 (cascade!)
        hwint_default 1

ALIGN   16
hwint03:                ; Interrupt routine for irq 3 (second serial)
        hwint_default 1

ALIGN   16
hwint04:                ; Interrupt routine for irq 4 (first serial)
        hwint_default 1

ALIGN   16
hwint05:                ; Interrupt routine for irq 5 (XT winchester)
        hwint_default 1

ALIGN   16
hwint06:                ; Interrupt routine for irq 6 (floppy)
        hwint_default 1

ALIGN   16
hwint07:                ; Interrupt routine for irq 7 (printer)
        hwint_default 1

ALIGN   16
hwint08:                ; Interrupt routine for irq 8 (realtime clock).
        hwint_default 1

ALIGN   16
hwint09:                ; Interrupt routine for irq 9 (irq 2 redirected)
        hwint_default 1

ALIGN   16
hwint10:                ; Interrupt routine for irq 10
        hwint_default 1
ALIGN   16
hwint11:                ; Interrupt routine for irq 11
        hwint_default 1

ALIGN   16
hwint12:                ; Interrupt routine for irq 12
        hwint_default 1

ALIGN   16
hwint13:                ; Interrupt routine for irq 13 (FPU exception)
       hwint_default 1

ALIGN   16
hwint14:                ; Interrupt routine for irq 14 (AT winchester)
       hwint_default 1

ALIGN   16
hwint15:                ; Interrupt routine for irq 15
        hwint_default 1

divide_error:
    push    0xFFFFFFFF
    push    0
    jmp exception
single_step_exception:
    push    0xFFFFFFFF
    push    1
    jmp exception
nmi:
    push    0xFFFFFFFF
    push    2
    jmp exception
breakpoint_exception:
    push    0xFFFFFFFF
    push    3
    jmp exception
overflow:
    push    0xFFFFFFFF
    push    4
    jmp exception
bounds_check:
    push    0xFFFFFFFF
    push    5
    jmp exception
inval_opcode:
    push    0xFFFFFFFF
    push    6
    jmp exception
copr_not_available:
    push    0xFFFFFFFF
    push    7
    jmp exception
double_fault:
    push    8
    jmp exception
copr_seg_overrun:
    push    0xFFFFFFFF
    push    9
    jmp exception
inval_tss:
    push    10
    jmp exception
segment_not_present:
    push    11
    jmp exception
stack_exception:
    push    12
    jmp exception
general_protection:
    push    13
    jmp exception
page_fault:
    push    14
    jmp exception
copr_error:
    push    0xFFFFFFFF
    push    16
    jmp exception

exception:
    call    exception_handler
    add esp, 4*2
    hlt

restart:
    mov esp, [p_proc_ready]
    lldt    [esp + P_LDT_SEL]
    lea eax, [esp + P_STACKTOP]
    mov dword [tss + TSS3_S_SP0], eax
restart_reenter:
    dec dword [k_reenter]
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 4
    iretd

save:
    pushad
    push ds
    push es
    push fs
    push gs
    mov dx, ss
    mov ds, dx
    mov es, dx

    mov esi, esp

    inc dword [k_reenter]
    cmp dword [k_reenter], 0
    jne .1
    mov esp, StackTop
    push restart
    jmp [esi + RETADR - P_STACKBASE]
.1:
    push restart_reenter
    jmp [esi + RETADR - P_STACKBASE]

