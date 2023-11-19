#include "SimpanMuat.h"
#include <sys/stat.h>
#include <time.h>

Word emptyWord = {{'\0', 0}};
void muat(char folderName[],AccountList *list, Graf *Teman, prioqueuefren *Q){
    char path[] = "../cfg/";
    char *folder = concatStr(path,folderName);

    if (!isDirExist(folder)){
        printf("Tidak ada folder yang dimaksud!\n");
    }else{
        for (int i=0;i<5;i++){
            if (i==0){ // User config
                ReadUser_FILE(concatStr(folder,"pengguna.config"),list,Teman, Q);
            }
            else if (i==1){ // Tweet config

            } 
            else if (i==2){ // Reply config

            }
            else if (i==3){ // Draft config

            }
            else if (i==4){ //Utas config

            }
        }
    }
}

void simpan(char folderName[]){
    // concat path to cfg folder
    char path[]= "../cfg/";
    if (!isDirExist(concatStr(path,folderName))){
        printf("Belum terdapat Folder1.\nAkan dilakukan pembuatan Folder1 terlebih dahulu.\n");
        printf("Mohon tunggu...\n1...\n2...\n3...\n%s sudah berhasil dibuat.\n",folderName);
    }
    for (int i= 0;i<5;i++){
        if (i==0){ // User config

        }
        else if (i==1){ // Tweet config

        } 
        else if (i==2){ // Reply config

        }
        else if (i==3){ // Draft config

        }
        else if (i==4){ //Utas config
            
        }
  
    }
}

boolean isDirExist(char path[]){
    struct stat stats;
    stat(path, &stats);

    if (S_ISDIR(stats.st_mode)){
        return true;
    }
    return false;
}
char* concatStr(char path[],char folder[]){
    int i;
    for (i=0;path[i]!='\0';i++);
    for (int j=0;folder[j]!='\0';j++){
        path[i] = folder[j];
        i++;
    }
    path[i] = '\0';
    return path;
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
void loadTweetCnfg(char filename[],KicauList* kList){
    int n;
    STARTFILE(filename);
    n = WordToInt(currentWord);
    int j;
    for (int i=0;i<n;i++){
        Kicau k;
        int id,like;
        Word tex;
        Word author;
        time_t date;
        j = 0;
        while (j<5)
        {
            ADVSENTENCE();
            if (j==0){
                id = WordToInt(currentWord);
            }
            else if (j==1) {
               CopyWord(&tex,currentWord);
            } 
            else if (j==2){
                like = WordToInt(currentWord);
            }
            else if (j==3){
                CopyWord(&author,currentWord);
            }else{
                struct tm tm = {0};
                strptime(currentWord.TabWord,"%d/%m/%Y %H:%M:%S",&tm);
                date = mktime(&tm);
            }
            j++;
        }
        CreateKicau(&k,author.TabWord);
        k.id = id;
        k.like = like;
        copyWordToString(k.text,tex);
        k.datetime = date;
        AddKicauToList(k,kList);
    }
}