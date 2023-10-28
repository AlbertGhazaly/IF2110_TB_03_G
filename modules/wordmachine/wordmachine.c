#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"

Word currentWord;
boolean EndWord;

void IgnoreBlanks() { 
    /* Mengabaikan satu atau beberapa BLANK
    I.S. : currentChar sembarang
    F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while (currentChar == BLANK && currentChar != MARK) {
        ADV();
    }
}

void IgnoreNewLine() {
    while (currentChar == '\n'&& currentChar)
    {
        ADV();
    }
}

void STARTWORD() { 
    /* I.S. : currentChar sembarang
    F.S. : EndWord = true, dan currentChar = MARK;
            atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
            currentChar karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlanks();
    IgnoreNewLine();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        EndWord = false;
        CopyWord();
    }

}

void ADVWORD() { 
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
    F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
            currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
            Jika currentChar = MARK, EndWord = true.
    Proses : Akuisisi kata menggunakan procedure SalinWord */
    IgnoreBlanks();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord() { 
    /* Mengakuisisi kata, menyimpan dalam currentWord
    I.S. : currentChar adalah karakter pertama dari kata
    F.S. : currentWord berisi kata yang sudah diakuisisi;
            currentChar = BLANK atau currentChar = MARK;
            currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
            Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK)) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    if (i < NMax) {
        currentWord.Length = i;
    } else {
        currentWord.Length = NMax;
    }
}

void CopyWordTo(Word *destination, Word source) {
    int i;
    for (i = 0; i < source.Length; i++) {
        destination->TabWord[i] = source.TabWord[i];
    }
    destination->Length = source.Length;
}