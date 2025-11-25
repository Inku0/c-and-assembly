; Lisame märgendi main globaalsesse nimeruumi
global main

; Deklareerime, et märgend printf asub globaalses nimeruumis
; ja ei ole defineeritud selles failis.
extern printf

; Algab programmi lähtekoodi sektsioon
section .text

; max(int x, int y)
; 1 local variable
max:
    ; stackil retr,x,y
    push ebp
    mov ebp, esp
    ; stackil ebp,retr,x,y

    ; int x = [ebp + 8]
    ; int y = [ebp + 12]

    ; reserve local variable
    ; int z = [ebp - 4]

    sub esp, 4 ; ehk 1 int
    
    mov ecx, [ebp + 8] ; ecx = x
    mov [ebp-4], ecx ; z = x

    mov eax, [ebp + 12] ; eax = y
    cmp eax, ecx ; if (x compare y)
    jl lopp ; if not -> else body aka if eax < ecx jump lopp

    mov [ebp - 4], eax ; z = y

lopp:

    ; z on suurim
    mov eax, [ebp - 4]
    ; taastame stacki
    add esp, 4

    mov esp, ebp
    pop ebp

    ret
; -------------------------------
; main funktsioon

; -------------------------------
main:
    push dword 3
    push dword 4

    call max ; eax = max(3, 4)
    add esp, 4*2 ; delete 3 and 4 (forget them behind)

    push eax ; eax = z
    push dword hello

    ; Kutsume välja printf funktsiooni.
    call printf

    add esp, 4*2

    mov eax, 0 

    ret

section .data

hello: db "Tulemus: %d", 10, 0
