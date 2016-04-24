
[SECTION .text]

global  memcpy
global  out_byte
global  in_byte
global  disable_int
global  enable_int
global memset
global  enable_irq
global  disable_irq
global  int33
global  int34
global  int35
global  int36

out_byte:
    mov edx, [esp + 4]      ; port
    mov al, [esp + 4 + 4]   ; value
    out dx, al
    nop ; 一点延迟
    nop
    ret
in_byte:
    mov edx, [esp + 4]      ; port
    xor eax, eax
    in  al, dx
    nop ; 一点延迟
    nop
    ret
memcpy:
    push    ebp
    mov ebp, esp

    push    esi
    push    edi
    push    ecx

    mov edi, [ebp + 8]
    mov esi, [ebp + 12]
    mov ecx, [ebp + 16]
.1:
    cmp ecx, 0
    jz  .2

    mov al, [ds:esi]
    inc esi

    mov byte [es:edi], al
    inc edi

    dec ecx
    jmp .1
.2:
    mov eax, [ebp + 8]

    pop ecx
    pop edi
    pop esi
    mov esp, ebp
    pop ebp

    ret

disable_int:
    cli
    ret

enable_int:
    sti
    ret

memset:
    push    ebp
    mov ebp, esp

    push    esi
    push    edi
    push    ecx

    mov edi, [ebp + 8]
    mov edx, [ebp + 12]
    mov ecx, [ebp + 16]
.1:
    cmp ecx, 0
    jz  .2

    mov byte [edi], dl
    inc edi

    dec ecx
    jmp .1
.2:

    pop ecx
    pop edi
    pop esi
    mov esp, ebp
    pop ebp

    ret

disable_irq:
        mov     ecx, [esp + 4]          ; irq
        pushf
        cli
        mov     ah, 1
        rol     ah, cl                  ; ah = (1 << (irq % 8))
        cmp     cl, 8
        jae     disable_8               ; disable irq >= 8 at the slave 8259
disable_0:
        in      al, 0x21
        test    al, ah
        jnz     dis_already             ; already disabled?
        or      al, ah
        out     0x21, al       ; set bit at master 8259
        popf
        mov     eax, 1                  ; disabled by this function
        ret
disable_8:
        in      al, 0xA1
        test    al, ah
        jnz     dis_already             ; already disabled?
        or      al, ah
        out     0xA1, al       ; set bit at slave 8259
        popf
        mov     eax, 1                  ; disabled by this function
        ret
dis_already:
        popf
        xor     eax, eax                ; already disabled
        ret

enable_irq:
        mov     ecx, [esp + 4]          ; irq
        pushf
        cli
        mov     ah, ~1
        rol     ah, cl                  ; ah = ~(1 << (irq % 8))
        cmp     cl, 8
        jae     enable_8                ; enable irq >= 8 at the slave 8259
enable_0:
        in      al, 0x21
        and     al, ah
        out     0x21, al       ; clear bit at master 8259
        popf
        ret
enable_8:
        in      al, 0xA1
        and     al, ah
        out     0xA1, al       ; clear bit at slave 8259
        popf
        ret
int33:
        int 33
        ret
int34:
        int 34
        ret
int35:
        int 35
        ret
int36:
        int 36
        ret
