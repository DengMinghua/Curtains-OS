[SECTION .data]

posx            dd  0
posy            dd  0
color            dd  0
char             dd  0
disp_pos            dd  0

[SECTION .text]

global  putchar
global  disp_str
global  disp_pos
global  putchar_kept

putchar:
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp + 8]
    mov     [char], eax
    mov     eax, [ebp + 12]
    mov     [color], eax
    mov     eax, [ebp + 16]
    mov     [posy], eax
    mov     eax, [ebp + 20]
    mov     [posx], eax

    mov     eax, [posx]
    mov     bx, 80
    mul     bx
    add     eax, [posy]
    mov     bx, 2
    mul     bx
    mov     edi,eax
    mov     eax, [color]
    shl     eax, 8
    or      eax, [char]
    cmp     al, 0Ah
    jnz .3
    push    eax
    mov     eax, [disp_pos]
    mov     bl, 160
    div     bl
    and     eax, 0FFh
    inc     eax
    mov     bl, 160
    mul     bl
    mov     [disp_pos], eax
    pop     eax
    push    eax
    push    ebx
    mov     eax,[disp_pos]
    mov     bx,2
    div     bx
    mov     ebx,eax
    mov  dx,03d4h
    mov al,0eh
    out dx,al
    inc dx
    mov al,bh
    out dx,al

    dec dx
    mov al,0fh
    out dx,al
    inc dx
    mov al,bl
    out dx,al
    pop ebx
    pop eax
    pop     ebp
    ret
.3:
    cmp     edi,0
    jnz     .4
    mov     edi,[disp_pos]
    add     edi,2
.4:
    mov     [disp_pos],edi
    push    eax
    push    ebx
    mov     eax,[disp_pos]
    mov     bx,2
    div     bx
    mov     ebx,eax
    mov  dx,03d4h
    mov al,0eh
    out dx,al
    inc dx
    mov al,bh
    out dx,al

    dec dx
    mov al,0fh
    out dx,al
    inc dx
    mov al,bl
    out dx,al
    pop ebx
    pop eax
    sub     edi,2
    mov     [gs:edi], ax
    pop     ebp
    ret

disp_str:
    push    ebp
    mov ebp, esp

    mov esi, [ebp + 8]
    mov edi, [disp_pos]
    mov ah, 0Fh
.1:
    lodsb
    test    al, al
    jz  .2
    cmp al, 0Ah
    jnz .3
    push    eax
    mov eax, edi
    mov bl, 160
    div bl
    and eax, 0FFh
    inc eax
    mov bl, 160
    mul bl
    mov edi, eax
    pop eax
    jmp .1
.3:
    mov [gs:edi], ax
    add edi, 2
    jmp .1

.2:
    mov [disp_pos], edi

    pop ebp
    ret

putchar_kept:
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp + 8]
    mov     [char], eax
    mov     eax, [ebp + 12]
    mov     [color], eax
    mov     eax, [ebp + 16]
    mov     [posy], eax
    mov     eax, [ebp + 20]
    mov     [posx], eax

    mov     eax, [posx]
    mov     bx, 80
    mul     bx
    add     eax, [posy]
    mov     bx, 2
    mul     bx
    mov     edi,eax
    mov     eax, [color]
    shl     eax, 8
    or      eax, [char]
    cmp     al, 0Ah
    jnz .3
    push    eax
    mov     eax, [disp_pos]
    mov     bl, 160
    div     bl
    and     eax, 0FFh
    inc     eax
    mov     bl, 160
    mul     bl
    pop     eax
    push    eax
    push    ebx
    mov     eax,[disp_pos]
    mov     bx,2
    div     bx
    mov     ebx,eax
    mov  dx,03d4h
    mov al,0eh
    out dx,al
    inc dx
    mov al,bh
    out dx,al

    dec dx
    mov al,0fh
    out dx,al
    inc dx
    mov al,bl
    out dx,al
    pop ebx
    pop eax
    pop     ebp
    ret
.3:
    cmp     edi,0
    jnz     .4
    mov     edi,[disp_pos]
    add     edi,2
.4:
    mov     [gs:edi], ax
    pop     ebp
    ret
