#include "includeADT.h"

void cetakUtas(int idUtas, KicauList kList,Account account, AccountList* listAccount,Graf teman){
    boolean isFound = false;
    Kicau* kicauan;
    Word privat = {"Privat",6};
    for (int i=0;(i<kList.count) && (!isFound);i++){
        if (kList.kicauan[i].utasKicau!=NULL){
            if (kList.kicauan[i].utasKicau->IDUtas == idUtas){
                isFound = true;
                *kicauan = kList.kicauan[i];
            }
        }
    }
    if (!isFound){
        printf("Utas tidak ditemukan!\n");
    }else{
        int i;
        for (i=0;!WordEqual(account.username[0],listAccount->accounts[i].username[0]);i++);
        int idUser = i;
        for (i=0;!WordEqual(kicauan->author,listAccount->accounts[i].username[0]);i++);
        int idTeman = i;
        
        if (WordEqual(listAccount->accounts[idTeman].jenisAkun[0],privat) && ELMTGRAF(teman,idUser,idTeman)==0){
            printf("Akun yang membuat utas ini adalah akun privat!\n Ikuti dahulu akun ini untuk melihat utasnya!\n");
            
        }else{
            printf("| ID = %d\n",kicauan->id);
            printf("| %s\n",kicauan->author.TabWord);
            struct tm *tm_struct = localtime(&kicauan->datetime);
            DATETIME local;
            CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
            printf("| ");TulisDATETIME(local);printf("\n");
            printf("| %s\n",kicauan->text);
            kSambungAdd kSam;
            kSam = kicauan->utasKicau->content;
            i = 0;
            while(kSam!=NULL){
                printf("   | INDEX = %d\n",i+1 );
                printf("   | %s\n",kSam->author.TabWord);
                tm_struct = localtime(&kSam->datetime);
                CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
                printf("   | " );TulisDATETIME(local);printf("\n");
                printf("   | %s\n",kSam->text);
                kSam = kSam->next;
                i++;
            }
            
        }
    }
}

kSambungAdd createKicauanSambung(Word tex, Account account){
    kSambungAdd kicauSam = (kSambungAdd)malloc(sizeof(KicauSambung));
    if (kicauSam!=NULL){
        kicauSam->next = NULL;
        copyWordToString((kicauSam->text), tex);
        CopyWordTo(&kicauSam->author,account.username[0]);
        kicauSam->datetime = time(NULL);
    }
    return kicauSam;
}

void sambungUtas(int idUtas,int index,  KicauList* kList,Account account){
    boolean isFound = false;
    Kicau* kicauan;
    for (int i=0;(i<kList->count) && (!isFound);i++){
        if (kList->kicauan[i].utasKicau!=NULL){
            if (kList->kicauan[i].utasKicau->IDUtas == idUtas){
                isFound = true;
                *kicauan = kList->kicauan[i];
            }
        }

    }
    if (!isFound){
        printf("Utas tidak ditemukan!\n");
    }else{
        if (!WordEqual(kicauan->author,account.username[0])){
            printf("Anda tidak bisa menyambung utas ini!\n");
        }else{
            int i =1;
            kSambungAdd kSam= kicauan->utasKicau->content;
            while (kSam->next!=NULL)
            {
                i++;
                kSam = kSam->next;
            }
            
            if (index<1){
                printf("Index terlalu rendah!\n");
            }else if (index>i+1){
                printf("Index terlalu tinggi!\n");
            }else{
                printf("Masukkan kicauan:\n");
                STARTSENTENCE();
                kSam = kicauan->utasKicau->content;
                kSambungAdd newKSam = createKicauanSambung(currentWord,account);
                if (index==1){
                    newKSam->next = kSam;
                    kicauan->utasKicau->content = newKSam;
                }else{
                    for (int j=2;j<index;j++){
                       kSam = kSam->next;
                    }
                    if ((kSam->next)==NULL){
                        kSam->next = newKSam;
                    }else{
                        newKSam->next = kSam->next;
                        kSam->next = newKSam;
                        
                    }
                }

            }
        }

    }


}

void hapusUtas(int idUtas, int index,KicauList* kList ,Account account){
    boolean isFound = false;
    Kicau* kicauan;
    for (int i=0;(i<kList->count) && (!isFound);i++){
        if (kList->kicauan[i].utasKicau!=NULL){
            if (kList->kicauan[i].utasKicau->IDUtas == idUtas){
                isFound = true;
                *kicauan = kList->kicauan[i];
            }
        }
    }
    if (!isFound){
        printf("Utas tidak ditemukan!\n");
    }else{
        if (!WordEqual(kicauan->author,account.username[0])){
            printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
        }else{
            if (index==0){
                printf("Anda tidak bisa menghapus kicauan utama!\n");
            }else{
                kSambungAdd kSam = kicauan->utasKicau->content;
                kSambungAdd delKSam;
                if (index==1){
                    delKSam = kSam;
                    kSam = kSam->next;
                    kicauan->utasKicau->content = kSam;
                    free(delKSam);
                }else{
                    for (int i=2;i<index&&kSam!=NULL;i++){
                        kSam = kSam->next;
                    }
                    if (kSam==NULL){
                        printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n",index);
                    }else{
                        delKSam = kSam->next;
                        kSam->next = delKSam->next;
                        free(delKSam);
                    }
                    
                }

            }
        }

    }
}

void createUtas(int id, KicauList* kList, Account account, int *jumlahUtas){
    Word ya = {"YA",2};
    Word tidak = {"TIDAK",5};
    boolean isFound = false;
    int i;
    for  (i=0;(i<kList->count)&& (!isFound);i++){
        if (kList->kicauan[i].id == id){
            isFound = true;
        }
    }
    if (!isFound){
        printf("Kicauan tidak ditemukan\n");
    }else{
        Kicau* kicau = &kList->kicauan[i];
        if (WordEqual(kicau->author,account.username[0])){
            printf("Utas ini bukan milik anda!\n");
        }else{
            if (kicau->utasKicau!=NULL){
                printf("Kicauan ini telah digunakan utas lain!\n");
            }else{
                boolean isStop = false;
                printf("Utas berhasil dibuat!\n");
                printf("Masukkan kicauan: \n");
                STARTSENTENCE();
                kSambungAdd kSam = createKicauanSambung(currentWord,account);
                kicau->utasKicau->content = kSam;
                *jumlahUtas++;
                kicau->utasKicau->IDUtas = *jumlahUtas;
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                STARTWORD();
                if (!lanjut){
                    isStop = true;
                }else{
                    isStop = false;
                }
                while (!isStop)
                {
                    printf("Masukkan kicauan:\n");
                    STARTSENTENCE();
                    kSam->next = createKicauanSambung(currentWord,account);
                    kSam = kSam->next;
                    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                    STARTWORD();
                    if (!lanjut){
                        isStop = true;
                    }else{
                        isStop = false;
                    }                    

                }
                printf("Utas selesai!\n");

            }
        }
    }
}

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
    Stack draf;
    CreateEmptyStack(&draf);
    ReadUser_FILE("../cfg/pengguna.config", &akun, &teman, &Q);
    ReadDraf_FILE("../cfg/draf.config", &akun, &draf);
    Stack drafStack[20]; // Buat 20 stack untuk 20 pengguna
    // int userID = 0;                  // ID pengguna saat ini
    // CreateEmpty(&drafStack[userID]); // Inisialisasi stack untuk pengguna saat ini
    int i;
    for(i = 0; i < 20; i++)
    {
        CreateEmptyStack(&drafStack[i]);
    }

    while (!IsEmptyStack(draf))
    {
        drafkicau temp;
        Pop(&draf, &temp);
        for(i = 0; i < 20; i++){
            if (temp.IDuser == i)
            {
                Push(&drafStack[i],temp);
            }
        }
    }

    Account akunLogin;
    KicauList kList;
    int idUtas = 0;


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
        Word utas = {"UTAS",4};
        Word sambung_utas = {"SAMBUNG_UTAS",12};
        Word hapus_utas = {"HAPUS_UTAS",10};
        Word cetak_utas = {"CETAK_UTAS",10};        
        Word buat_draf = {"BUAT_DRAF", 9};

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
        else if (wordCheck(command,0,3,utas)) //utas
        {
            int i= 5;
            int id = 0;
            while (i<command.Length)
            {
                id *=10;
                id += CharToInt(command.TabWord[i]);
                i++;
            }
            createUtas(id,&kList,akunLogin,&idUtas);
        }else if (wordCheck(command,0,11,sambung_utas)) //sambung utas
        {
            int idUtas=0;
            int index = 0;
            int i= 13;
            while (command.TabWord[i]!=' ')
            {
                idUtas *=10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            i++;
            while (command.TabWord[i]!=MARKACC)
            {
                index *=10;
                index += CharToInt(command.TabWord[i]);
                i++;
            }
            sambungUtas(idUtas,index,&kList,akunLogin);
            
        }else if(wordCheck(command,0,9,hapus_utas)) //hapus utas
        {
            int idUtas=0;
            int index = 0;
            int i= 11;
            while (command.TabWord[i]!=' ')
            {
                idUtas *=10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            i++;
            while (command.TabWord[i]!=MARKACC)
            {
                index *=10;
                index += CharToInt(command.TabWord[i]);
                i++;
            }
            hapusUtas(idUtas,index,&kList,akunLogin);
        }else if(wordCheck(command,0,9,cetak_utas)) //cetak utas
        {
            int idUtas = 0;
            int i = 11;
            while (command.TabWord[i]!=MARKACC)
            {
                idUtas *=10;
                idUtas += CharToInt(command.TabWord[i]);
                i++;
            }
            cetakUtas(idUtas,kList,akunLogin,akun,teman);
            
        }
        else if(WordEqual(command, buat_draf))
        {
            int idUser;
            i = 0;
            boolean found = false;
            while(i < akun.count && found == false)
            {
                if(WordEqual( *akun.accounts[i].username, *akunLogin.username))
                {
                    idUser = i;
                    found = true;
                }
                i++; 
            }
            if(isLogin){
                buatdraf(drafStack, idUser, &akun);
            }
            else{
                printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
            }
        }
        else{
            printf("Perintah tidak valid!\n");
        }
    }
    ADVCOMMAND();
    return 0;
}