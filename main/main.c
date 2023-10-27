
#include "includeADT.h"
#include "functions.c"

int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;
    
    // Array untuk menampung user saat ini
    // ListStatik currentUser;
    // CreateListStatik(&currentUser);

    
    while (runProgram) {
        printf(">> ");
        STARTWORD();
        // printf(">> ");
        // fflush(stdin);

        Word command = currentWord;
        Word tutup_program = {"TUTUP_PROGRAM", 13};
        Word daftar = {"DAFTAR", 6};
        Word masuk = {"MASUK", 6};
        Word keluar = {"KELUAR", 6};

        if (WordEqual(command, tutup_program)){
            runProgram = false; 
        }
        ADVWORD();
    }
    return 0;
}