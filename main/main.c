#include "includeADT.h"
#include "functions.c"


int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    boolean runProgram = true;

    //Array untuk menampung user saat ini
    AccountList akun;
    CreateAccountList(&akun);

    Word account[20] = {{'\0', 0}};
    boolean isLogin = false;
    while (runProgram) {
        printf(">> ");
        STARTWORD();

        Word command = currentWord;
        Word tutup_program = {"TUTUP_PROGRAM", 13};
        Word daftar = {"DAFTAR", 6};
        Word masuk = {"MASUK", 5};
        Word keluar = {"KELUAR", 6};
        Word ganti_profil = {"GANTI_PROFIL", 12};
        Word curr_user = {"USER", 4};

        if (WordEqual(command, tutup_program)){
            runProgram = false;
        }
        else if (WordEqual(command, daftar)){
            if(IsAccountListFull(&akun)){
                printf("Batas jumlah pengguna sudah tercapai, tidak dapat menambahkan akun baru.\n");
            }
            else{
                signup(&akun);
            }

        }
        else if(WordEqual(command, masuk)){
            if (isLogin){
                printf("Anda sudah login dengan akun %s\n", account);
            }
            else{
                printf("Masukkan nama: ");
                STARTWORD();
                Word attemptUsername = currentWord;
                while(attemptUsername.Length > 20){
                    printf("Nama terlalu panjang, masukkan maksimal 20 karakter!\n");
                    printf("Masukkan nama: ");
                    STARTWORD();
                    attemptUsername = currentWord;
                }
                while(!IsUsernameInAccountList(&akun, attemptUsername)){
                    printf("Tidak ada akun dengan nama tersebut, silahkan masukkan nama lain.\n");
                    printf("Masukkan nama: ");
                    STARTWORD();
                    attemptUsername = currentWord;
                }
                ADVWORD();
                printf("Masukkan kata sandi: ");
                STARTWORD();
                Word attemptPassword = currentWord;
                while(attemptPassword.Length > 20){
                    printf("Kata sandi terlalu panjang, masukkan maksimal 20 karakter!\n");
                    printf("Masukkan kata sandi: ");
                    STARTWORD();
                    attemptPassword = currentWord;
                }
                while(!cekPassword(&akun, attemptUsername, attemptPassword)){
                    printf("Kata sandi salah, coba lagi.\n");
                    printf("Masukkan kata sandi: ");
                    STARTWORD();
                    attemptPassword = currentWord;
                }
                ADVWORD;
                inUser(account, attemptUsername);
                isLogin = true;
                printf("Selamat datang, %s!\n", account);

            }
        }
        else if(WordEqual(command, keluar)){
            if (!isLogin){
                printf("Anda belum login, sehingga tidak bisa keluar.\n");
            }
            else{
                printf("Keluar dari akun dengan username %s\n", account);
                outUser(account);
                isLogin = false;
            }
        }
        else if(WordEqual(command, ganti_profil)){
            if(isLogin == false){
                printf("Anda belum masuk, silakan masuk terlebih dahulu.\n");
            }
            else{
                edit_account(&akun, account[0]);
            }
        }
        else if(WordEqual(command, curr_user)){
            DisplayAccounts(&akun);
        }

        else{
            printf("Tidak ada perintah %s", currentWord);
        }
        ADVWORD();
    }
    printf("%s", account[0].TabWord);
    return 0;
}