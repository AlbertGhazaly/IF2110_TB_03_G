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
    while(IsUsernameInAccountList(listakun, attemptUsername)){
        printf("Nama tersebut sudah dipakai, silahkan masukkan nama lain!\n");
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
    ADVWORD;
    CreateAccount(&akun, attemptUsername, attemptPassword);
    AddAccountToList(listakun, akun);
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