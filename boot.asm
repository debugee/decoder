
%ifdef BIN_FORMAT
org 0x7C00
%endif
bits 16
global start
start:
    mov al, 0x7f
    rol al, 8
    
    mov si, msg         ; SI 指向字符串
    call print_string

.halt:
    hlt
    jmp .halt

; 打印字符串，SI 指向以 0 结尾的字符串
print_string:
    mov ah, 0x0E        ; BIOS INT 10h, TTY 输出
    mov bh, 0           ; 页码
.loop:
    lodsb               ; AL = [SI], SI++
    test al, al         ; 检查是否为 0（字符串结尾）
    jz .done
    int 0x10            ; BIOS 打印字符
    jmp .loop
.done:
    ret

msg db 'Hello, World!', 0x0D, 0x0A, 0   ; 字符串，\r\n 结尾

times 510-($-$$) db 0
dw 0xAA55