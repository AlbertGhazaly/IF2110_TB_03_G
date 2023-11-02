#include "Pengguna.h"

Word emptyWord = {{'\0', 0}};
Word privat = {"Privat", 6};
Word publik = {"Publik", 6};

Word yes = {"y", 1};
Word no = {"n", 1};

Word wetonJawa[] = {
        {"pon", 3},
        {"wage", 4},
        {"kliwon", 6},
        {"legi", 4},
        {"pahing", 6}
    };

void inUser(Account *account, Word username){
    *Username(*account) = username;
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
            displayMatrixChar(list->accounts->fotoprofil);
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

void ReadUser_FILE(char filename[], AccountList *list, Graf *teman){
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
            ELMTGRAF(*teman,i,j) = CharToInt(currentWord.TabWord[j*2]);
        }
        ADVSENTENCE();
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
    printf("| Nama: %s\n", list->accounts[GetAccountIdx(list, user)].username);
    printf("| Bio Akun: %s\n", list->accounts[GetAccountIdx(list, user)].bio);
    printf("| No HP: %s\n", list->accounts[GetAccountIdx(list, user)].noHP);
    printf("| Weton: %s\n", list->accounts[GetAccountIdx(list, user)].weton);
    
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

    ADVSENTENCE();
    STARTSENTENCE();
    printf("Masukkan No HP: ");
    STARTSENTENCE();
    Word attemptNoHP = currentWord;
    while(attemptNoHP.Length > 20 || !isPhoneNumberValid(currentWord)){
        STARTSENTENCE();
        printf("No HP tidak valid, masukkan No HP yang valid!\n");
        printf("Masukkan No HP: ");
        STARTSENTENCE();
        attemptNoHP = currentWord;
    }

    if (!WordEqual(attemptNoHP, emptyWord)){
        CopyWordTo(list->accounts[GetAccountIdx(list, user)].noHP, attemptNoHP);
    }

    ADVSENTENCE();
    STARTSENTENCE();
    printf("Masukkan Weton: ");
    STARTSENTENCE();
    Word attemptWeton = currentWord;
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

void ganti_jenis_akun(AccountList *list, Account user){
    if(WordEqualAccount(*list->accounts[GetAccountIdx(list, user)].jenisAkun, publik)){
        STARTSENTENCE();
        printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (Y/N): ");
        STARTSENTENCE();
        Word attemptJenis = currentWord;
        while(!(WordEqual(toLowerCase(attemptJenis), yes) || WordEqual(toLowerCase(attemptJenis), no))){
            STARTSENTENCE();
            printf("Input tidak valid!\n");
            printf("Saat ini, akun Anda adalah akun Publik. Ingin mengubah ke akun Privat? (Y/N): ");
            STARTSENTENCE();
            attemptJenis = currentWord;
        }
        ADVSENTENCE();

        if(WordEqual(attemptJenis, yes)){
            CopyWordTo(list->accounts[GetAccountIdx(list, user)].jenisAkun, privat);
            printf("Akun anda sudah diubah menjadi akun Privat.\n");
        }
        else{
            printf("Akun anda tetap akun Publik.\n");
        }
    }
    else{
        STARTSENTENCE();
        printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (Y/N): ");
        STARTSENTENCE();
        Word attemptJenis = currentWord;
        while(!(WordEqual(toLowerCase(attemptJenis), yes) || WordEqual(toLowerCase(attemptJenis), no))){
            STARTSENTENCE();
            printf("Input tidak valid!\n");
            printf("Saat ini, akun Anda adalah akun Privat. Ingin mengubah ke akun Publik? (Y/N): ");
            STARTSENTENCE();
            attemptJenis = currentWord;
        }
        ADVSENTENCE();

        if(WordEqual(attemptJenis, yes)){
            CopyWordTo(list->accounts[GetAccountIdx(list, user)].jenisAkun, publik);
            printf("Akun anda sudah diubah menjadi akun Publik.\n");
        }
        else{
            printf("Akun anda tetap akun Privat.\n");
        }
    }
}