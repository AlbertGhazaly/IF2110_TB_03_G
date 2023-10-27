#include "includeADT.h"
#include "functions.c"

int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;
    
    // Array untuk menampung user saat ini
    Word User[1] = {{'\0', 0}};
    
    STARTWORD();
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
        else if (WordEqual(command, daftar)){
            Word smodeng = {"Smodeng", 7};
            setUser(User, smodeng);
        }
        ADVWORD();
    }
    printf("%s", User[0].TabWord);
    return 0;
}