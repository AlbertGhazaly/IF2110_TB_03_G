#include "Pengguna.h"

Word emptyWord = {{'\0', 0}};
Word privat = {"Privat", 6};
Word publik = {"Publik", 6};

void inUser(Word *array, Word username){
    array[0] = username;
}
void outUser(Word *array){
    Word emptyWord = {{'\0', 0}};
    array[0] = emptyWord;
}

void CreateAccount(Account *account, Word username, Word password){
    CopyWordTo(Username(*account), username);
    CopyWordTo(Password(*account), password);
    CopyWordTo(Bio(*account), emptyWord);
    CopyWordTo(NoHP(*account), emptyWord);
    CopyWordTo(Weton(*account), emptyWord);
    CopyWordTo(JenisAkun(*account), publik);
}

void signup(AccountList *listakun){
    Account akun;
    printf("Masukkan nama: ");
    STARTWORD();
    Word attemptUsername = currentWord;
    while(attemptUsername.Length > 20){
        printf("Nama terlalu panjang, masukkan maksimal 20 karakter!\n");
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

    ADVWORD();
    CreateAccount(&akun, attemptUsername, attemptPassword);
    AddAccountToList(listakun, akun);
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
    printf("\nAkun berhasil ditambahkan ke daftar pengguna. Silahkan masuk untuk menikmati fitur Burbir.\n");
}

void DisplayAccounts(AccountList *list){
    if (list->count == 0) {
        printf("Tidak ada akun dalam list.\n");
    } else {
        int i;
        for (i = 0; i < list->count; i++) {
            printf("Akun %d:\n", i + 1);
            printf("Username: %s\n", list->accounts[i].username);
            printf("Password: %s\n", list->accounts[i].password);
            printf("Bio Akun: %s\n", list->accounts[i].bio);
            printf("No HP: %s\n", list->accounts[i].noHP);
            printf("Weton: %s\n", list->accounts[i].weton);
            printf("Jenis Akun: %s\n", list->accounts[i].jenisAkun);
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
        if (WordEqualAccount(list->accounts[i].username[0], username)) {
            found = true;
        } else {
            i++;
        }
    }
    return found;
}

int GetAccountIdx(AccountList *list, Word username) {
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(list->accounts[i].username[0], username)) {
            found = true;
        } else {
            i++;
        }
    }
    return i;
}

boolean cekPassword(AccountList *list, Word username, Word password){
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(list->accounts[i].username[0], username) && WordEqualAccount(list->accounts[0].password[0], password)) {
            found = true;
        } else {
            i++;
        }
    }
    return found;
}

void ReadUser_FILE(char filename[], AccountList *list, Matrix *teman){
    int N;
    STARTWORD_FILE(filename);
    //Akuisisi Nilai N
    N = WordToInt(currentWord);
    printf("%d\n", N);
    ADVSENTENCE();
    int i;
    for (i = 0; i < N; i++)
    {
        printf("test\n");
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
                printWord(currentWord);
            }
            else if (currentChar == '\n' && j == 1)
            {
                CopyWordTo(Password(akun), currentWord);
                j++;
                printWord(currentWord);
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
                j++;
            }
            ADVSENTENCE();
        }
        AddAccountToList(list, akun);
    }
}
//"../cfg/map.txt"

void edit_account(AccountList *list, Word user){
    printf("| Nama: %s\n", list->accounts[GetAccountIdx(list, user)].username);
    printf("| Bio Akun: %s\n", list->accounts[GetAccountIdx(list, user)].bio);
    printf("| No HP: %s\n", list->accounts[GetAccountIdx(list, user)].noHP);
    printf("| Weton: %s\n", list->accounts[GetAccountIdx(list, user)].weton);
    
    printf("Masukkan Bio Akun: ");
    STARTWORD();
    Word attemptBio = currentWord;
    while(attemptBio.Length > 135){
        printf("Bio akun terlalu panjang, masukkan maksimal 135 karakter!\n");
        printf("Masukkan Bio Akun: ");
        STARTWORD();
        attemptBio = currentWord;
    }

    if (!WordEqual(attemptBio, emptyWord)){
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].bio, attemptBio);
    }

    ADVWORD();
    printf("Masukkan No HP: ");
    STARTWORD();
    Word attemptNoHP = currentWord;
    while(attemptNoHP.Length > 20){
        printf("No HP tidak valid, masukkan No HP yang valid!\n");
        printf("Masukkan No HP: ");
        STARTWORD();
        attemptNoHP = currentWord;
    }

    if (!WordEqual(attemptNoHP, emptyWord)){
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].noHP, attemptNoHP);
    }

    ADVWORD;
    printf("Masukkan Weton: ");
    STARTWORD();
    Word attemptWeton = currentWord;
    while(attemptWeton.Length > 20){
        printf("Weton tidak valid, masukkan Weton yang valid!\n");
        printf("Masukkan Weton: ");
        STARTWORD();
        attemptWeton = currentWord;
    }
    ADVWORD;

    if (!WordEqual(attemptWeton, emptyWord)){
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].bio, attemptWeton);
    }
}