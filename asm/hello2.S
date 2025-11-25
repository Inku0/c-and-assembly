; Lisame märgendi main globaalsesse nimeruumi
global main

; Deklareerime, et märgend printf asub globaalses nimeruumis
; ja ei ole defineeritud selles failis.
extern printf

; Algab programmi lähtekoodi sektsioon
section .text
; -------------------------------
; main funktsioon

; -------------------------------
main:
    ; printf("Hello world!\n");
    ; Paneme magasini sõne "Hello world!" aadressi (4 baiti), mille
    ; tulemusena registri esp väärtus *väheneb* 4 võrra.
    push esp
    push dword 2
    push dword 1
    push hello

    ; Kutsume välja printf funktsiooni.
    call printf

    ; Kustutame sõne aadressi magasini tipust, selleks suurendame
    ; magasini tipule viitava registri esp väärtust 4 võrra.
    add esp, 4*4

    ; return 0;
    ; Registrist eax loetakse funktsiooni tagastusväärtus, kui see on
    ; oma töö lõpetanud.
    mov eax, 0 

    ; Lõpetame main funktsiooni töö.
    ret

; Algab andmete ala
section .data

; Märgend hello on pelgalt aadress, millel asuvad järgnevad andmed.
; väärtus 10 on reavahetus ja eriti oluline on lõpus olev 0, mis
; näitab, et selles kohas lõppeb sõne!
hello: db 'Loendur: %d %d %d', 10, 0
