; translated from BF: ++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++. 
global main
section .text
main:
	push esi
	push edi
	mov ecx, 7500
	mem_init:
		push dword 0
		loop mem_init
	mov esi, esp
	mov edi, 0
	mov al, [esi+edi]
	add al, 8
	mov [esi+edi], al
	blp_1:
		mov eax, 0
		mov al, [esi+edi]
		cmp eax, 0
		je elp_30
	add edi, 1
	mov al, [esi+edi]
	add al, 4
	mov [esi+edi], al
	blp_4:
		mov eax, 0
		mov al, [esi+edi]
		cmp eax, 0
		je elp_16
	add edi, 1
	mov al, [esi+edi]
	add al, 2
	mov [esi+edi], al
	add edi, 1
	mov al, [esi+edi]
	add al, 3
	mov [esi+edi], al
	add edi, 1
	mov al, [esi+edi]
	add al, 3
	mov [esi+edi], al
	add edi, 1
	mov al, [esi+edi]
	add al, 1
	mov [esi+edi], al
	sub edi, 4
	mov al, [esi+edi]
	sub al, 1
	mov [esi+edi], al
		jmp blp_4
	elp_16:
	add edi, 1
	mov al, [esi+edi]
	add al, 1
	mov [esi+edi], al
	add edi, 1
	mov al, [esi+edi]
	add al, 1
	mov [esi+edi], al
	add edi, 1
	mov al, [esi+edi]
	sub al, 1
	mov [esi+edi], al
	add edi, 2
	mov al, [esi+edi]
	add al, 1
	mov [esi+edi], al
	blp_24:
		mov eax, 0
		mov al, [esi+edi]
		cmp eax, 0
		je elp_27
	sub edi, 1
		jmp blp_24
	elp_27:
	sub edi, 1
	mov al, [esi+edi]
	sub al, 1
	mov [esi+edi], al
		jmp blp_1
	elp_30:
	add edi, 2
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	add edi, 1
	mov al, [esi+edi]
	sub al, 3
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov al, [esi+edi]
	add al, 7
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov al, [esi+edi]
	add al, 3
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	add edi, 2
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	sub edi, 1
	mov al, [esi+edi]
	sub al, 1
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	sub edi, 1
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov al, [esi+edi]
	add al, 3
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov al, [esi+edi]
	sub al, 6
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	mov al, [esi+edi]
	sub al, 8
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	add edi, 2
	mov al, [esi+edi]
	add al, 1
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	add edi, 1
	mov al, [esi+edi]
	add al, 2
	mov [esi+edi], al
	mov eax, 4
	mov ebx, 1
	lea ecx, [esi+edi]
	mov edx, 1
	int 0x80
	add esp, 30000
	pop esi
	pop edi
	exit:
		mov eax, 1
		xor ebx, ebx
		int 0x80
