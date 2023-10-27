
#include "includeADT.h"
#include "functions.c"

int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;
    
    // Array untuk menampung user saat ini
    // ListStatik currentUser;
    // CreateListStatik(&currentUser);

    
    Word User[20] = {{"\0", 0}};
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
        Word curr_user = {"USER", 4};

        if (WordEqual(command, tutup_program)){
            runProgram = false; 
        }
        else if (WordEqual(command, daftar)){
            Word smodeng = {"Smodeng", 7};
            setUser(User, smodeng);
        }
        else if(WordEqual(command, curr_user)){
            printf("Current user: %s\n", User);
        }
        ADVWORD();
    }
    return 0;
}