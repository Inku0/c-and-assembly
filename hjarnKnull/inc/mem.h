#pragma once

/*
 * suurendab indeksiga viidatud massiivi elemendi väärtust ühe võrra. Tagastab uue väärtuse.
 */
int mem_inc(void);

/*
 * vähendab indeksiga viidatud massiivi elemendi väärtust ühe võrra. Tagastab uue väärtuse.
 */
int mem_dec(void);

/*
 * liigutab indeksit vasakuke (vähendab selle väärtust ühe võrra). Kui indeks muutub negatiivseks, siis liiguta see massiivi lõppu. Tagastab indeksi uue väärtuse.
 */
int mem_left(void);

/*
 * liigutab indeksit paremale (suurendab selle väärtust ühe võrra). Kui indeks läheb üle massiivi piiri, siis liiguta indeks massiivi algusesse. Tagastab indeksi uue väärtuse.
 */
int mem_right(void);

/*
 * tagastab antud indeksil oleva väärtuse.
 */
int mem_get(void);

/*
 * salvestab väärtuse praegusele indeksile ja tagastab selle väärtuse.
 */
int mem_set(char v);

/*
 * trükib välja indeksi väärtuse, mälu väärtuse sellel indeksil ja sellele järgnevad 9 väärtust (kui massiivi piir tuleb ette, siis liigu tagasi algusesse). Formaadi näidis:
 * index: 10 mem [10 .. 19]: 7 6 10 -12 55 22 0 0 0 0
 */
void mem_printDebug(void);
