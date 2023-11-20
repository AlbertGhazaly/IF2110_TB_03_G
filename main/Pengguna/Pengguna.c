#include "Pengguna.h"

Word emptyWord = {{'\0', 0}};
Word privat = {"Privat", 6};
Word publik = {"Publik", 6};

Word yes = {"ya", 2};
Word no = {"tidak", 5};

Word wetonJawa[] = {
        {"pon", 3},
        {"wage", 4},
        {"kliwon", 6},
        {"legi", 4},
        {"pahing", 6}
    };

MatrixChar default_foto(){
    MatrixChar mc;
    createMatrixchar(5, 10, &mc);
    int i, j;
    for (i = 0; i < 5; i++){
        for (j = 0; j < 10; j++){
            if( j % 2 == 0){
                ELMTChar(mc, i, j) = 'R';
            }
            else{
                ELMTChar(mc, i, j) = '*';
            }
        }
    }
    return mc;
}

void inUser(Account *account, Word username){
    *Username(*account) = emptyWord;
    CopyWordTo(Username(*account), username);
}
void outUser(Account *account){
    *Username(*account) = emptyWord;
}

void CreateAccount(Account *account, Word username, Word password){
    CopyWordTo(Username(*account), username);
    CopyWordTo(Password(*account), password);
    CopyWordTo(Bio(*account), emptyWord);
    CopyWordTo(NoHP(*account), emptyWord);
    CopyWordTo(Weton(*account), emptyWord);
    CopyWordTo(JenisAkun(*account), publik);
    copyMatrixChar(default_foto(), &FotoProfil(*account));
}

void signup(AccountList *listakun){
    Account akun;
    STARTSENTENCE();
    printf("Masukkan nama: ");
    STARTSENTENCE();
    Word attemptUsername = currentWord;
    while(attemptUsername.Length > 20){
        STARTSENTENCE();
        printf("Nama terlalu panjang, masukkan maksimal 20 karakter!\n");
        printf("Masukkan nama: ");
        STARTSENTENCE();
        attemptUsername = currentWord;
    }
    
    while(IsUsernameInAccountList(listakun, attemptUsername)){
        STARTSENTENCE();
        printf("Nama tersebut sudah terdaftar, masukkan nama lain!\n");
        printf("Masukkan nama: ");
        STARTSENTENCE();
        attemptUsername = currentWord;
    }

    ADVSENTENCE();
    STARTSENTENCE();
    printf("Masukkan kata sandi: ");
    STARTSENTENCE();
    Word attemptPassword = currentWord;
    while(attemptPassword.Length > 20){
        STARTSENTENCE();
        printf("Kata sandi terlalu panjang, masukkan maksimal 20 karakter!\n");
        printf("Masukkan kata sandi: ");
        STARTSENTENCE();
        attemptPassword = currentWord;
    }

    ADVSENTENCE();
    CreateAccount(&akun, attemptUsername, attemptPassword);
    AddAccountToList(listakun, akun);
    printf("\nAkun berhasil ditambahkan ke daftar pengguna. Silahkan masuk untuk menikmati fitur Burbir.\n");
}

void signin(AccountList *akun, Account *akunLogin){
    if(isEmptyAccountList(akun)){
        printf("Tidak ada akun terdaftar.\n\n");
    }
    else{
        STARTSENTENCE();
        printf("Masukkan nama: ");
        STARTSENTENCE();
        Word attemptUsername = currentWord;
        while(attemptUsername.Length > 20){
            STARTSENTENCE();
            printf("Nama terlalu panjang, masukkan maksimal 20 karakter!\n");
            printf("Masukkan nama: ");
            STARTSENTENCE();
            attemptUsername = currentWord;
        }
        while(!IsUsernameInAccountList(akun, attemptUsername)){
            STARTSENTENCE();
            printf("Tidak ada akun dengan nama tersebut, silahkan masukkan nama lain.\n");
            printf("Masukkan nama: ");
            STARTSENTENCE();
            attemptUsername = currentWord;
        }
        ADVSENTENCE();

        STARTSENTENCE();
        printf("Masukkan kata sandi: ");
        STARTSENTENCE();
        Word attemptPassword = currentWord;
        while(attemptPassword.Length > 20){
            STARTSENTENCE();
            printf("Kata sandi terlalu panjang, masukkan maksimal 20 karakter!\n");
            printf("Masukkan kata sandi: ");
            STARTSENTENCE();
            attemptPassword = currentWord;
        }
        while(!cekPassword(akun, attemptUsername, attemptPassword)){
            STARTSENTENCE();
            printf("Kata sandi salah, coba lagi.\n");
            printf("Masukkan kata sandi: ");
            STARTSENTENCE();
            attemptPassword = currentWord;
        }
        ADVSENTENCE();
        inUser(akunLogin, attemptUsername);
        printf("Selamat datang, ");
        printWord(attemptUsername);
        printf("!\n\n");
    }
}

boolean isEmptyAccountList(AccountList *list){
    return list->count == 0;
}

void CreateAccountEmpty(Account *account) {
    *Username(*account) = emptyWord;
    *Password(*account) = emptyWord;
    *Bio(*account) = emptyWord;
    *NoHP(*account) = emptyWord;
    *Weton(*account) = emptyWord;
    *JenisAkun(*account) = emptyWord;
}

void CreateAccountList(AccountList *list) {
    list->count = 0;
}

void AddAccountToList(AccountList *list, Account account){
    list->accounts[list->count] = account;
    list->count++;
}

void DisplayAccounts(AccountList *list){
    if (list->count == 0) {
        printf("Tidak ada akun dalam list.\n\n");
    } else {
        int i;
        for (i = 0; i < list->count; i++) {
            printf("Akun %d:\n", i + 1);
            printf("Username: %s\n", list->accounts[i].username[0].TabWord);
            printf("Password: %s\n", list->accounts[i].password[0].TabWord);
            printf("Bio Akun: %s\n", list->accounts[i].bio[0].TabWord);
            printf("No HP: %s\n", list->accounts[i].noHP[0].TabWord);
            printf("Weton: %s\n", list->accounts[i].weton[0].TabWord);
            printf("Jenis Akun: %s\n\n", list->accounts[i].jenisAkun[0].TabWord);
            printf("Foto Profil:\n");
            colorizedProfil(list->accounts[i].fotoprofil);
            printf("\n");
        }
    }
}

boolean IsAccountListFull(AccountList *list){
    return list->count >= MAX_ACCOUNTS;
}

boolean WordEqualAccount(Word a, Word b) {
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

boolean IsUsernameInAccountList(AccountList *list, Word username) {
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(*list->accounts[i].username, username)) {
            found = true;
        }
        i++;
    }
    return found;
}

int GetAccountIdx(AccountList *list, Account account){
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(*list->accounts[i].username, *Username(account))) {
            found = true;
        }
        i++;
    }
    return i-1;
}

boolean cekPassword(AccountList *list, Word username, Word password){
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(*list->accounts[i].username, username) && WordEqualAccount(*list->accounts[i].password, password)) {
            found = true;
        }
        i++;
    }
    return found;
}

void ReadUser_FILE(char filename[], AccountList *list, Graf *Teman, prioqueuefren *Q){
    int N;
    STARTWORD_FILE(filename);
    //Akuisisi Nilai N
    N = WordToInt(currentWord);
    ADVSENTENCE();
    int i,j;
    for (i = 0; i < N; i++)
    {
        Word username, password, bio, noHP, weton, jenisakun;
        Matrix profil;
        Account akun;
        CreateAccountEmpty(&akun);
        int j = 0;
        int batas = 11;
        while (j < batas)
        {
            if (currentChar == '\n' && j == 0)
            {
                CopyWordTo(Username(akun), currentWord);
                j++;
            }
            else if (currentChar == '\n' && j == 1)
            {
                CopyWordTo(Password(akun), currentWord);
                j++;
            }
            else if (currentChar == '\n' && j == 2)
            {
                if (WordEqual(*Password(akun),currentWord))
                {
                    CopyWordTo(Bio(akun), emptyWord);
                }
                else
                {
                    CopyWordTo(Bio(akun), currentWord);
                }
                j++;
            }
            else if (currentChar == '\n' && j == 3)
            {
                if (WordEqual(*Bio(akun), currentWord) || WordEqual(*Password(akun),currentWord))
                {
                    CopyWordTo(NoHP(akun), emptyWord);
                }
                else
                {
                    CopyWordTo(NoHP(akun), currentWord);
                }
                j++;
            }
            else if (currentChar == '\n' && j == 4)
            {
                if (WordEqual(*Bio(akun), currentWord) || WordEqual(*Password(akun),currentWord) || WordEqual(*NoHP(akun), currentWord))
                {
                    CopyWordTo(Weton(akun), emptyWord);
                }
                else{
                    CopyWordTo(Weton(akun), currentWord);
                }
                j++;
            }
            else if (currentChar == '\n' && j == 5)
            {
                CopyWordTo(JenisAkun(akun), currentWord);
                j++;
            }
            else if (currentChar == '\n' && j > 5 && j < 11)
            {
                //Foto Profil pengguna.config disini
                createMatrixchar(5, 10, &akun.fotoprofil);
                int k;
                for(k = 0; k < 10; k++){
                    ELMTChar(akun.fotoprofil,j-6,k) = currentWord.TabWord[k*2];
                }
                j++;
            }
            ADVSENTENCE();
        }
        AddAccountToList(list, akun);
    }
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            ELMTGRAF(*Teman,i,j) = CharToInt(currentWord.TabWord[j*2]);
        }
        ADVSENTENCE();
    }
    int countQ = WordToInt(currentWord);
    if(countQ != 0)
    {
        for(i = 0; i < countQ-1; i++){
            ADVSENTENCE();
            teman temp;
            for(j = 0; j < 3; j++){
                if(j == 0){
                    temp.IDpengirim = CharToInt(currentWord.TabWord[j*2]);
                }
                if(j == 1){
                    temp.IDpenerima = CharToInt(currentWord.TabWord[j*2]);
                }
                if(j == 2){
                    temp.Jumlahteman = CharToInt(currentWord.TabWord[j*2]);
                }
            }
            Enqueueprio(Q, temp);
        }
        i = 0;
        teman temp;
        while (i < 5){
            ADV();
            if(i == 0){
                temp.IDpengirim = CharToInt(currentChar);
            }
            else if(i == 2){
                temp.IDpenerima = CharToInt(currentChar);
            }
            else if (i == 4){
                temp.Jumlahteman = CharToInt(currentChar);
            }
            i++;
        }
        Enqueueprio(Q, temp);
    }
}

boolean isPhoneNumberValid(const Word phoneNumber) {
    for (int i = 0; i < phoneNumber.Length; i++) {
        char c = phoneNumber.TabWord[i];
        if (!((c >= '0' && c <= '9') || c == '+' || c == '-')) {
            return false;
        }
    }
    return true;
}

boolean isWetonJawa(Word word) {
    int i;
    for (i = 0; i < sizeof(wetonJawa) / sizeof(wetonJawa[0]); i++) {
        if (word.Length == wetonJawa[i].Length) {
            int j;
            boolean match = true;
            for (j = 0; j < word.Length; j++) {
                if (word.TabWord[j] != wetonJawa[i].TabWord[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

Word toLowerCase(Word word) {
    Word result;
    int length = word.Length;
    result.Length = length;

    for (int i = 0; i < length; i++) {
        if (word.TabWord[i] >= 'A' && word.TabWord[i] <= 'Z') {
            result.TabWord[i] = word.TabWord[i] + 32;
        } else {
            result.TabWord[i] = word.TabWord[i];
        }
    }
    return result;
}

void edit_profile(AccountList *list, Account user){
    currentWord = emptyWord;
    printf("| Nama: %s\n", list->accounts[GetAccountIdx(list, user)].username->TabWord);
    printf("| Bio Akun: %s\n", list->accounts[GetAccountIdx(list, user)].bio->TabWord);
    printf("| No HP: %s\n", list->accounts[GetAccountIdx(list, user)].noHP->TabWord);
    printf("| Weton: %s\n\n", list->accounts[GetAccountIdx(list, user)].weton->TabWord);
    
    STARTSENTENCE();
    printf("Masukkan Bio Akun: ");
    STARTSENTENCE();
    Word attemptBio = currentWord;
    while(attemptBio.Length > 135){
        STARTSENTENCE();
        printf("Bio akun terlalu panjang, masukkan maksimal 135 karakter!\n");
        printf("Masukkan Bio Akun: ");
        STARTSENTENCE();
        attemptBio = currentWord;
    }

    if (!WordEqual(attemptBio, emptyWord)){
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].bio, attemptBio);
    }
    currentWord = emptyWord;
    ADVSENTENCE();
    STARTSENTENCE();
    printf("Masukkan No HP: ");
    STARTSENTENCE();
    Word attemptNoHP = currentWord;
    if (!WordEqual(attemptNoHP, emptyWord)){
        while(attemptNoHP.Length > 20 || !isPhoneNumberValid(currentWord)){
            STARTSENTENCE();
            printf("No HP tidak valid, masukkan No HP yang valid!\n");
            printf("Masukkan No HP: ");
            STARTSENTENCE();
            attemptNoHP = currentWord;
        }
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].noHP, attemptNoHP);
    }
    currentWord = emptyWord;
    ADVSENTENCE();
    STARTSENTENCE();
    printf("Masukkan Weton: ");
    STARTSENTENCE();
    Word attemptWeton = currentWord;
    if (!WordEqual(attemptWeton, emptyWord)){
        while(attemptWeton.Length > 20 || !isWetonJawa(toLowerCase(attemptWeton))){
            STARTSENTENCE();
            printf("Weton tidak valid, masukkan Weton yang valid!\n");
            printf("Masukkan Weton: ");
            STARTSENTENCE();
            attemptWeton = currentWord;
        }
        ADVSENTENCE();

        if (!WordEqual(attemptWeton, emptyWord)){
            CopyWordTo(list->accounts[GetAccountIdx(list, user)].weton, attemptWeton);
        }
    }
    printf("Akun anda berasil diperbaharui!\n\n");
}

void ganti_jenis_akun(AccountList *list, Account user){
    if(WordEqualAccount(*list->accounts[GetAccountIdx(list, user)].jenisAkun, publik)){
        currentWord = emptyWord;
        STARTSENTENCE();
        printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (YA/TIDAK): ");
        STARTSENTENCE();
        Word attemptJenis = currentWord;
        while(!(WordEqual(toLowerCase(attemptJenis), yes) || WordEqual(toLowerCase(attemptJenis), no))){
            STARTSENTENCE();
            printf("Input tidak valid!\n");
            printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (YA/TIDAK): ");
            STARTSENTENCE();
            attemptJenis = currentWord;
            printWord(attemptJenis);
        }
        ADVSENTENCE();
        if(WordEqual(toLowerCase(attemptJenis), yes)){
            CopyWordTo(list->accounts[GetAccountIdx(list, user)].jenisAkun, privat);
            printf("Akun anda sudah diubah menjadi akun Privat.\n\n");
        }
        else{
            printf("Akun anda tetap akun Publik.\n\n");
        }
    }
    else{
        currentWord = emptyWord;
        STARTSENTENCE();
        printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (YA/TIDAK): ");
        STARTSENTENCE();
        Word attemptJenis = currentWord;
        while(!(WordEqual(toLowerCase(attemptJenis), yes) || WordEqual(toLowerCase(attemptJenis), no))){
            STARTSENTENCE();
            printf("Input tidak valid!\n");
            printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (YA/TIDAK): ");
            STARTSENTENCE();
            attemptJenis = currentWord;
        }
        ADVSENTENCE();

        if(WordEqual(toLowerCase(attemptJenis), yes)){
            CopyWordTo(list->accounts[GetAccountIdx(list, user)].jenisAkun, publik);
            printf("Akun anda sudah diubah menjadi akun Publik.\n\n");
        }
        else{
            printf("Akun anda tetap akun Privat.\n\n");
        }
    }
}

void colorizedProfil(MatrixChar mc){
    int i, j;
    for (i = 0; i < ROW_EFFChar(mc); i++){
        for (j = 0; j < COL_EFFChar(mc) - 1; j++){
            if(ELMTChar(mc, i, j) == 'R'){
                print_red(ELMTChar(mc, i, j + 1));
            }
            else if(ELMTChar(mc, i, j) == 'G'){
                print_green(ELMTChar(mc, i, j + 1));
            }
            else if(ELMTChar(mc, i, j) == 'B'){
                print_blue(ELMTChar(mc, i, j + 1));
            }
        }
        printf("\n");
    }
}

void edit_foto(AccountList *list, Account user){
    printf("Foto Profil:\n");
    colorizedProfil(list->accounts[GetAccountIdx(list, user)].fotoprofil);
    printf("Masukkan foto profil baru:\n");
    int i, j;
    STARTSENTENCE();
    ADVSENTENCE();
    for (i = 0; i < ROW_EFFChar(list->accounts[GetAccountIdx(list, user)].fotoprofil); i++){
        for (j = 0; j < COL_EFFChar(list->accounts[GetAccountIdx(list, user)].fotoprofil); j++){
            ELMTChar(list->accounts[GetAccountIdx(list, user)].fotoprofil,i,j) = currentWord.TabWord[j*2];
        }
        ADVSENTENCE();
    }
    printf("Foto profil berhasil diubah!\n\n");
}

void show_profile(AccountList *l, Word username){
    int i = 0;
    boolean found = false;
    while (!found && i < l->count) {
        if (WordEqualAccount(*l->accounts[i].username, username)) {
            found = true;
        }
        i++;
    }
    if(found){
        printf("| Nama: %s\n", l->accounts[i-1].username->TabWord);
        printf("| Bio Akun: %s\n", l->accounts[i-1].bio->TabWord);
        printf("| No HP: %s\n", l->accounts[i-1].noHP->TabWord);
        printf("| Weton: %s\n", l->accounts[i-1].weton->TabWord);
        printf("| Jenis Akun: %s\n\n", l->accounts[i-1].jenisAkun->TabWord);
        printf("| Foto Profil:\n");
        colorizedProfil(l->accounts[i-1].fotoprofil);
        printf("\n");
    }
    else{
        printf("Username tidak ditemukan.\n\n");
    }
}

void PrintPrioQueue (prioqueuefren Q, AccountList * listakun)
{
    if(IsEmptyPrio(Q))
    {
        printf("Tidak ada permintaan pertemanan untuk Anda.\n");
    }
    else{
        int count = NBElmtPrio(Q);
        printf("Terdapat %d permintaan pertemanan untuk Anda.\n", count);
        printf("\n");
        int i = HeadQ(Q);
        while (i != TailQ(Q)+1){
            teman temp = Q.T[i];
            printf("| ");
            printWord(*listakun->accounts[temp.IDpengirim].username);
            printf("\n");
            printf("| Jumlah teman: %d\n\n", temp.Jumlahteman);
            i = (i + 1) % MaxElQ(Q);
        }
    }
}

void PrintTopPrioQueueChar (prioqueuefren Q, int IDuser, AccountList * listakun, int *idteman)
{
    if(IsEmptyPrio(Q))
    {
        printf("Tidak ada permintaan pertemanan untuk Anda.\n");
    }
    else{
        teman temp;
        printf("Permintaan pertemanan teratas dari ");
        printWord(*listakun->accounts[IDuser].username);
        printf("\n\n");
        int i = HeadQ(Q);
        temp = Q.T[i];
        printf("| ");
        printWord(*listakun->accounts[temp.IDpengirim].username);
        printf("\n");
        printf("| Jumlah teman: %d\n\n", temp.Jumlahteman);
        *idteman = temp.IDpengirim;
    }
}

void ReadDraf_FILE(char filename[], AccountList *list, Stack *S){
/*Membaca file Draf dari Draf.config kedalam program
    I.S. Stack terdefinisi dan AccountList sudah diakuisisi dari user.config
    F.S. Stack terisi dengan drafkicauan dari Draf.Config
    */
    int N;
    STARTWORD_FILE(filename);
    N = WordToInt(currentWord);
    int i;
    for(i = 0; i < N; i++)
    {
        ADVSENTENCE();
        Word user;
        int jumlah;
        int j;
        CopyWordTo(&user, currentWord);
        user.Length = user.Length - 2;
        int idAkun;
        int i = 0;
        boolean found = false;
        while(i < list->count && found == false)
        {
            if(WordEqual(*list->accounts[i].username, user))
            {
                idAkun = i;
                found = true;
            }
            i++; 
        }
        jumlah = CharToInt(currentWord.TabWord[currentWord.Length-1]);
        for(j = 0; j < jumlah; j++)
        {
            drafkicau DrafKicau;
            DATETIME waktudraf;
            ADVSENTENCE();
            Word draf = currentWord;
            ADVSENTENCE();
            int k;
            Word dd;
            for(k = 0; k < 2; k++){
                dd.TabWord[k] = currentWord.TabWord[k];
            }
            dd.Length = 2;
            int DD = WordToInt(dd);
            Word mm;
            for(k = 3; k < 5; k++){
                mm.TabWord[k-3] = currentWord.TabWord[k];
            }
            mm.Length = 2;
            int MM = WordToInt(mm);
            Word yy;
            for(k = 6; k < 10; k++){
                yy.TabWord[k-6] = currentWord.TabWord[k];
            }
            yy.Length = 4;
            int YY = WordToInt(yy);
            Word hh;
            for(k = 11; k < 13; k++){
                hh.TabWord[k-11] = currentWord.TabWord[k];
            }
            hh.Length = 2;
            int HH = WordToInt(hh);
            Word m;
            for(k = 14; k < 16; k++){
                m.TabWord[k-14] = currentWord.TabWord[k];
            }
            m.Length = 2;
            int M = WordToInt(m);
            Word ss;
            for(k = 17; k < 19; k++){
                ss.TabWord[k-17] = currentWord.TabWord[k];
            }
            ss.Length = 2;
            int SS = WordToInt(ss);
            CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
            DrafKicau.Draf = draf;
            DrafKicau.IDuser = idAkun;
            DrafKicau.waktu = waktudraf;
            Push(S, DrafKicau);
        }
    }
}
