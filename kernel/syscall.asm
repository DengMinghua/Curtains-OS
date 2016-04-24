%include "sconst.inc"

global INT_VECTOR_SYS_CALL_1

INT_VECTOR_SYS_CALL_33 equ 0x33
INT_VECTOR_SYS_CALL_34 equ 0x33
INT_VECTOR_SYS_CALL_35 equ 0x33
INT_VECTOR_SYS_CALL_36 equ 0x33


global get_ticks;

bits 32
[section .text]

get_ticks:
int INT_VECTOR_SYS_CALL_33
ret



