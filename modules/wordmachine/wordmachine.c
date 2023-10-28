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
    while (currentChar == '\n'&& currentChar != MARK)
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

void CopyWordSpace()
/*Mengakuisisi kata, dengan enter atau NewLine sebagai MARK*/
{
   int i = 0;
   while (currentChar != MARKBaris){
      currentWord.TabWord[i] = currentChar;
      ADV();
      i++;
   }

   if (i > NMax){
      currentWord.Length = NMax;
   }

   else{
      currentWord.Length = i;
   }
}

void printWord(Word w) 
{
    int i;
    for (i = 0; i < w.Length; i++) {
        printf("%c", w.TabWord[i]);
    }
    printf("\n");
    printf("%d\n", w.Length);
}

void STARTSENTENCE()
/* I.S. : currentChar sembarang
   F.S. : Mengakuisisi kata dengan pembatas NEWLINE terhadap kata berikutnya*/
{
   START();
   if (currentChar == MARKBaris){
      EndWord = true;
   }
   else{
      EndWord = false;
      CopyWordSpace();
   }
}

void STARTWORD_FILE(char filename[])
/*Pita dari file eksternal siap dibaca oleh mesin kata. MARKFile merupakan NULL atau \0 dimana EndWord akan (menyala) bernilai TRUE saat
    Pita menyentuh NULL atau \0.*/
{
   START_FILE(filename);
   IgnoreBlanks();
   if (currentChar == MARKFile){
      EndWord = true;
   }
   else{
      EndWord = false;
      ADVWORD();
   }
}

boolean WordEqual(Word a, Word b) 
/*Mengirimkan true apabila Word a dan Word b identik.*/
{
    if (a.Length != b.Length) {
        return false;
    } else {
        int n = a.Length;

        boolean equal = true;
        int i = 0;
        while (equal && (i < n)) {
            if ((a.TabWord[i] != b.TabWord[i])) {
                equal = false;
            } else {
                i += 1;
            }
        }

        return equal;
    }
}

int WordToInt(Word string)
/*I.S. Kata yang telah diakuisi berisi string bilangan [0..9].
   F.S. Mengembalikan nilai integer dari kata yang diakuisisi.*/
{
    int hasil = 0;
    int i;
    for (i=0; i<string.Length; i++){
        hasil = hasil * 10 + (string.TabWord[i] - 48);
    }

    if (hasil < 0){
        int bilangan = 1;
        for (i=0; i<string.Length-1; i++){
            bilangan = bilangan * 10;
        }
        hasil += 38 * bilangan;
        }
}

Word stringToWord(char character[], int length)
/*Mengubah character(char) menjadi sebuah kata(Word).*/
{
    int i;
    Word strWord;

    strWord.Length = length;
    for (i = 0; i < length; i++)
    {
        strWord.TabWord[i] = character[i];
    }

    return strWord;
}