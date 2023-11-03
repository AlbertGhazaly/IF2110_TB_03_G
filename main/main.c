#include "includeADT.h"



int main() {
    printf("Selamat datang di Burbir. Selamat berkicau!\n\n");

    //Utilities
    boolean login = false;
    boolean runProgram = true;
    //Array untuk menampung user saat ini
    AccountList akun;
    CreateAccountList(&akun);
    Graf teman;
    createEmptyGraf(&teman);
    ReadUser_FILE("../cfg/pengguna.config", &akun, &teman);
    Account akunLogin;

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
        Word jenis_akun = {"ATUR_JENIS_AKUN", 15};
        Word ubah_foto = {"UBAH_FOTO_PROFIL", 16};
        Word curr_user = {"USER", 4};
        Word daftar_teman = {"DAFTAR_TEMAN", 12};
        Word hapus_teman = {"HAPUS_TEMAN", 11};


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
                printf("Anda sudah login dengan akun %s\n", akunLogin.username->TabWord);
            }
            else{
                signin(&akun, &akunLogin);
                isLogin = true;
            }
        }
        
        else if(WordEqual(command, ganti_profil)){
            if(!isLogin){
                printf("Anda belum login, silahkan login terlebih dahulu.\n");
            }
            else{
                edit_profile(&akun, akunLogin);
            }
        }

        else if(WordEqual(command, keluar)){
            if (!isLogin){
                printf("Anda belum login, sehingga tidak bisa keluar.\n");
            }
            else{
                printf("Keluar dari akun dengan username %s\n", akunLogin.username->TabWord);
                outUser(&akunLogin);
                isLogin = false;
            }
        }

        else if(WordEqual(command, jenis_akun)){
            if(!isLogin){
                printf("Anda belum login, silahkan login terlebih dahulu.\n");
            }
            else{
                ganti_jenis_akun(&akun, akunLogin);
            }
        }

        else if(WordEqual(command, ubah_foto)){

        }

        else if(WordEqual(command, curr_user)){
            DisplayAccounts(&akun);
        }
        else if (WordEqual(command,daftar_teman)){
            daftarteman(isLogin, akunLogin, &akun, teman);
        }
        else if (WordEqual(command,hapus_teman)){
            hapusteman(isLogin, akunLogin, &akun, &teman);
        }
        

        ADVWORD();
    }
    return 0;
}