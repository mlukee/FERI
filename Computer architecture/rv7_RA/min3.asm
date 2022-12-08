extern scanf
extern printf

section .data
	vpis1: db "Vnesi prvo stevilo: ", 0
    vpis2: db "Vnesi drugo stevilo: ", 0
    vpis3: db "Vnesi tretje stevilo: ", 0
    izpisNajvecje: db "Najvecje stevilo je: ", 0
	izpisN: db "%d", 10, 0			; izpisujem i v novi vrstici
	format: db "%d", 0				; uporabim pri scanf

section .bss
st_1 resb 1 ; 4 bajti za 32-bitno stevilo
st_2 resb 1
st_3 resb 1

section .text
global main

main:
	;push rbp ; shranim rbp
	;mov rbp, rsp ; nastavim rbp na vrh stacka
    ;sub rsp, 16
    call preberi_stevila ;pridobim 3 stevila

    ; Nastavim si vsa tri stevila
    ;mov rdi, [st_1] ; rdi 1st argument
    ;mov rsi, [st_2] ; rsi 2nd argument
   ; mov rdx, [st_3] ; rdx 3rd argument

   ; call najvecje_stevilo  ;klicem funkcijo katera poisce MAX

    ;mov rsi, rax ; shranim najvecje stevilo
    ;lea rdi, izpisNajvecje
    ;call printf
    
    ;pop rbp
    ;mov rax, 0
    ;leave
    ret

;Preberem 3 stevila iz konzole
preberi_stevila:
	mov rdi, [vpis1] ; nalozim naslov sporocila -> rdi = vpis
    mov rax, 0
	call printf ; printf(vpis1)

	;preberi stevilo 1
	mov eax, 0 
	lea rdi, [format] ; nalozim naslov formata -> rdi = format
	lea rsi, [st_1] ; nalozim naslov spremenljivke -> rsi = st_1
	call scanf ; scanf(format, &st_1)

    xor eax, eax ; eax = 0
	lea rdi, [vpis2] ; nalozim naslov sporocila -> rdi = vpis
	call printf ; printf(vpis2)

	;preberi stevilo 2
	mov eax, 0 
	lea rdi, [format] ; nalozim naslov formata -> rdi = format
	lea rsi, [st_2] ; nalozim naslov spremenljivke -> rsi = n
	call scanf ; scanf(format, &st_2)

    xor eax, eax ; eax = 0
	lea rdi, [vpis3] ; nalozim naslov sporocila -> rdi = vpis
	call printf ; printf(vpis3)

	;preberi stevilo 3
	mov eax, 0 
	lea rdi, [format] ; nalozim naslov formata -> rdi = format
	lea rsi, [st_3] ; nalozim naslov spremenljivke -> rsi = n
	call scanf ; scanf(format, &st_3)
    ret ;vrnem se v main

;najvecje_stevilo:
 ;   cmp rdi, rsi ;Primerjam st_1 z st_2
  ;  jl drugoAliTretje ; ce je st_1 manjse od st_2
   ; cmp rdi, rdx ;Primerjam st_1 z st_3
    ;jl drugoAliTretje
    ;mov rax, rdi ; st_1 je najvecje zato ga shranim
    ;ret ;grem iz funkcije

;drugoAliTretje:
 ;   cmp rsi, rdx ;primerjam st_2 z st_3
  ;  jl tretjeMax ; ce je st_2 manjse od st_3 potem st_3 = MAX
   ; mov rax, rsi ; drugace je st_2 MAX
    ;ret

;tretjeMax:
 ;   mov rax, rdx ;shranim st_3
  ;  ret