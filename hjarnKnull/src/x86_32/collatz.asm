global collatz
section .text

; Funktsioonide illustreerimiseks loome funktsiooni nimega collaz, mis saab parameetriks ühe positsiivse täisarvu n ja
; tagastab n/2 kui n on paarisarv ja 3*n+1. Kuna assembleri funktsioonid on niigi keerulised lugeda, siis on mõistlik
; kõik funktsioonid võimalusel panna eraldi faili, aga jällegi pole otseselt kohustuslik. Loome faili collaz.asm.old:

collatz:
	; prologue
	push ebp 		; make room for base pointer on the stack
	mov ebp, esp	; set base pointer to current stack pointer

	; body
	mov eax, [ebp + 8] ; 8 bytes from base pointer lies the function's argument

	mov ecx, 2 ; divider

	mov edx, 0 ; clean edx, gonna be holding the remainder from division
	div ecx ; takes from eax, divides with ecx, puts into **eAx**

	cmp edx, 0 ; check if edx == 0 aka it is an even number -> eax already stores n / 2 so can return early
	je end ; Jump when Equal (to end), otherwise continue

	mov eax, [ebp + 8] ; it's not even -> it's odd, reassign it to eax because eax currently stores the int from div

	mov ecx, 3 ; put 3 into ecx
	mul ecx ; takes from eax, multiplies with ecx, puts into eAx
	add eax, 1 ; add 1 to eax

end:
	; epilogue
	mov esp, ebp ; return stack pointer to base
	pop ebp ; pop ebp off the stack, it's no longer needed
	ret ; clean up