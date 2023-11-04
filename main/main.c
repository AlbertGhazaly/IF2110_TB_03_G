#include "includeADT.h"



int main() {

    //Utilities
    boolean login = false;
    boolean runProgram = true;

    //Array untuk menampung user saat ini
    AccountList akun;
    CreateAccountList(&akun);
    Graf teman;
    createEmptyGraf(&teman);
    prioqueuefren Q;
    MakeEmptyprio(&Q,100);
    ReadUser_FILE("../cfg/pengguna.config", &akun, &teman, &Q);
    Account akunLogin;

    boolean isLogin = false;
    printf("           ____  __  __  ____  ____  ____  ____ /\\ \n");
    printf("    __    (  _ \\(  )(  )(  _ \\(  _ \\(_  _)(  _ \\)(    __    \n");
    printf("___( o)>   ) _ < )(__)(  )   / ) _ < _)(_  )   /\\/  <(o )___\n");
    printf("\\ <_. )   (____/(______)(_)\\_)(____/(____)(_)\\_)()   ( ._> /\n");
    printf(" `---'              Tempat Anda Mencibir              `---' \n\n");

    printf("Selamat datang di Burbir. Selamat berkicau!\n");
    while (runProgram) {
        printf(">> ");
        STARTCOMMAND();
        
        Word command = currentWord;
        Word tutup_program = {"TUTUP_PROGRAM", 13};
        Word daftar = {"DAFTAR", 6};
        Word masuk = {"MASUK", 5};
        Word keluar = {"KELUAR", 6};
        Word ganti_profil = {"GANTI_PROFIL", 12};
        Word jenis_akun = {"ATUR_JENIS_AKUN", 15};
        Word ubah_foto = {"UBAH_FOTO_PROFIL", 16};
        Word lihat_profil = {"LIHAT_PROFIL", 12};
        Word curr_user = {"USER", 4};
        Word daftar_teman = {"DAFTAR_TEMAN", 12};
        Word hapus_teman = {"HAPUS_TEMAN", 11};
        Word tambah_teman = {"TAMBAH_TEMAN", 12};
        Word daftar_permintaan_teman = {"DAFTAR_PERMINTAAN_PERTEMANAN", 28};
        Word setujui_pertemanan = {"SETUJUI_PERTEMANAN", 18};

        if (WordEqual(command, tutup_program)){
            runProgram = false;
        }
        else if (WordEqual(command, daftar)){
            if (isLogin){
                printf("Anda sedang login dengan akun %s, silahkan keluar dulu.\n", akunLogin.username->TabWord);
            }
            else if(IsAccountListFull(&akun)){
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
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else{
                edit_profile(&akun, akunLogin);
            }
        }

        else if(WordEqual(command, keluar)){
            if (!isLogin){
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else{
                printf("Keluar dari akun dengan username %s\n", akunLogin.username->TabWord);
                outUser(&akunLogin);
                isLogin = false;
            }
        }

        else if(WordEqual(command, jenis_akun)){
            if(!isLogin){
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else{
                ganti_jenis_akun(&akun, akunLogin);
            }
        }

        else if(WordEqual(command, ubah_foto)){
            if(!isLogin){
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else{
                edit_foto(&akun, akunLogin);
            }
        }

        else if(WordEqual(command, curr_user)){
            DisplayAccounts(&akun);
        }
        else if (WordEqual(command,hapus_teman)){
            hapusteman(isLogin, akunLogin, &akun, &teman);
        }
        else if (WordEqual(command, tambah_teman)){
            tambahteman(isLogin, akunLogin, &akun, teman, &Q);
        }
        else if (WordEqual(command, daftar_permintaan_teman)){
            daftarpermintaanteman(isLogin, akunLogin, &akun, &Q);
        }
        else if (WordEqual(command, setujui_pertemanan)){
            setujuipermintaanteman(isLogin, akunLogin, &akun, &teman, &Q);
        }
        else if(wordCheck(command, 0, 11, lihat_profil) && command.Length > 12){
            if(!isLogin){
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
            else{
                show_profile(&akun, wordFromIndex(command, 13));
            }
        }
        else{
            printf("Perintah tidak valid!\n");
        }
    }
    ADVCOMMAND();
    return 0;
}