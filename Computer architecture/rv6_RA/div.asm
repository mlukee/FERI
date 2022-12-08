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

	mov DWORD [i],1 ; i = 1

    ; za div potrebujem eax in ecx
    ; EDX/EAX
    mov eax,[n]
    mov ecx, 2
    div ecx ; Delim n/2
    ; Rezultat = EAX
    ; Ostanek = EDX
    mov DWORD [n], eax ;n nadomestim z n/2

loop:
	;for loop
    xor edx, edx ; edx = 0, ostanek vedno resetiram
    mov eax, [i] ; v eax dam i
    mov ebx, 47  ; v ebx dam 47
    div ebx    ; delim i/47
    cmp edx, 0 ;primerjam ce je ostanek 0
    jne .preskoci ;jne => jump if not equal

	mov edx, [n] ; edx = n/2
	mov rsi, [i];	; rsi = i
	lea rdi, [izpisN] ; nalozim naslov formata -> rdi = izpisN
	xor eax, eax ; eax = 0
	call printf ; printf(izpisN, i)

.preskoci:
	mov ecx, DWORD[n] ; ecx = n

	add DWORD [i], 1 ; i = i + 1

	cmp [i], ecx ; primerjam i in n
	jle loop ;	ce je i < n, skoci na loop

	add rsp, 16 ; popravim stack
	leave 		;  == mov rsp, rbp && pop rbp
	ret

;pomoc -> https://www.youtube.com/watch?v=5eWiz3soaEM&t=832&ab_channel=SolidusCode