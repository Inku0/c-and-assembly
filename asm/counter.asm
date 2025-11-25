global main
extern printf
section .text
main:
    ; initialize counter to 10
    mov ecx, 10          ; ecx will hold the counter value

loop_begin:
    cmp ecx, 0           ; compare counter with 0
    je loop_end          ; Jump if Equal (to loop_end)
    ; otherwise
    push ecx             ; push ecx to stack

    push ecx             ; push ecx again?
    push count

    call printf          ; printf consumes two things (count and then ecx)

    add esp, 8           ; shrink stack by 8 aka 2 things

    pop ecx              ; get ecx value from stack

    dec ecx              ; decrement ecx

    jmp loop_begin

loop_end:
    mov eax, 0
    ret

section .data
count: db "counter: %d", 10, 0