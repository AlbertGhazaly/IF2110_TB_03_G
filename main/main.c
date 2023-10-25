#include <stdio.h>
#include "includeADT.h"
#include "functions.c"

int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;
    STARTWORD();
    while (runProgram) {
        EndWord = false;
        // printf(">> ");
        // fflush(stdin);

        Word command = currentWord;
        Word keluar = {"KELUAR", 6};

        if (WordEqual(command, keluar)) {
            runProgram = false; 
        }
        ADVWORD();
    }
    return 0;
}