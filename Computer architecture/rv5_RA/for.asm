extern scanf
extern printf

section .data
	vpis: db "Vnesi N: ", 0	
	izpisN: db "%d", 10, 0			; izpisujem i v novi vrstici
	format: db "%d", 0				; uporabim pri scanf

section .bss
i resb 4 ; 4 bajti za i
n resb 4 ; 4 bajti za 32-bitno stevilo -> N

section .text
global main

main:
	push rbp ; shranim rbp
	mov rbp, rsp ; nastavim rbp na vrh stacka
	sub rsp, 16 ; rezerviram prostor za i

	;telo programa

	;izpisi navodilo za vnos
	xor eax, eax ; eax = 0
	lea rdi, [vpis] ; nalozim naslov sporocila -> rdi = vpis
	call printf ; printf(vpis)

	;preberi stevilo
	mov eax, 0 
	lea rdi, [format] ; nalozim naslov formata -> rdi = format
	lea rsi, [n] ; nalozim naslov spremenljivke -> rsi = n
	call scanf ; scanf(format, &n)

	mov DWORD [i],1 ; i = 0

loop:
	;for loop
	mov edx, [n] ; edx = n
	mov rsi, [i];	; rsi = i
	lea rdi, [izpisN] ; nalozim naslov formata -> rdi = izpisN
	xor eax, eax ; eax = 0
	call printf ; printf(izpisN, i)

	mov ecx, DWORD[n] ; ecx = n
	add DWORD [i], 1 ; i = i + 1

	cmp [i], ecx ; primerjam i in n
	jl loop ;	ce je i < n, skoci na loop

	add rsp, 16 ; popravim stack
	leave 		;  == mov rsp, rbp && pop rbp
	ret

;pomoc -> https://www.youtube.com/watch?v=5eWiz3soaEM&t=832&ab_channel=SolidusCode