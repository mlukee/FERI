section .text
    global _start
_start:
    mov rax, 1     ; mov rax, 1 => 1 premaknem v rax     |
    mov rdi, 1	   ; file descriptor 1 => STDOUT_FILENO  |
    mov rsi, msg   ; string shranim v rsi 		 |=> sys_write(1, msg, 25)
    mov rdx, 25    ; velikost stringa			 |
    syscall        ;                                     |
    
    mov rax, 60    ;           |
    mov rdi, 0     ; ni napake |=> sys_exit(0)  
    syscall        ;           |
    ret

section .data:
    msg: db "Matic Lukezic E1133422", 0xa  ; 0xA pomeni nova vrstica
    
    ;pomoc => https://www.youtube.com/watch?v=BWRR3Hecjao&ab_channel=kupala
