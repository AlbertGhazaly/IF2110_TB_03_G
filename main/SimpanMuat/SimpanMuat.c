// #include "SimpanMuat.h"
// #include <sys/stat.h>
// #include <time.h>

// void muat(char folderName[],AccountList *list, Graf *Teman, prioqueuefren *Q){
//     char path[] = "../cfg/";
//     char *folder = concatStr(path,folderName);

//     if (!isDirExist(folder)){
//         printf("Tidak ada folder yang dimaksud!\n");
//     }else{
//         for (int i=0;i<5;i++){
//             if (i==0){ // User config
//                 ReadUser_FILE(concatStr(folder,"pengguna.config"),list,Teman, Q);
//             }
//             else if (i==1){ // Tweet config

//             } 
//             else if (i==2){ // Reply config

//             }
//             else if (i==3){ // Draft config

//             }
//             else if (i==4){ //Utas config

//             }
//         }
//     }
// }

// void simpan(char folderName[]){
//     // concat path to cfg folder
//     char path[]= "../cfg/";
//     if (!isDirExist(concatStr(path,folderName))){
//         printf("Belum terdapat Folder1.\nAkan dilakukan pembuatan Folder1 terlebih dahulu.\n");
//         printf("Mohon tunggu...\n1...\n2...\n3...\n%s sudah berhasil dibuat.\n",folderName);
//     }
//     for (int i= 0;i<5;i++){
//         if (i==0){ // User config

//         }
//         else if (i==1){ // Tweet config

//         } 
//         else if (i==2){ // Reply config

//         }
//         else if (i==3){ // Draft config

//         }
//         else if (i==4){ //Utas config
            
//         }
  
//     }
// }

// boolean isDirExist(char path[]){
//     struct stat stats;
//     stat(path, &stats);

//     if (S_ISDIR(stats.st_mode)){
//         return true;
//     }
//     return false;
// }
// char* concatStr(char path[],char folder[]){
//     int i;
//     for (i=0;path[i]!='\0';i++);
//     for (int j=0;folder[j]!='\0';j++){
//         path[i] = folder[j];
//         i++;
//     }
//     path[i] = '\0';
//     return path;
// }
// // Load
// void ReadUser_FILE(char filename[], AccountList *list, Graf *Teman, prioqueuefren *Q){
//     int N;
//     STARTWORD_FILE(filename);
//     //Akuisisi Nilai N
//     N = WordToInt(currentWord);
//     ADVSENTENCE();
//     int i,j;
//     for (i = 0; i < N; i++)
//     {
//         Word username, password, bio, noHP, weton, jenisakun;
//         Matrix profil;
//         Account akun;
//         CreateAccountEmpty(&akun);
//         int j = 0;
//         int batas = 11;
//         while (j < batas)
//         {
//             if (currentChar == '\n' && j == 0)
//             {
//                 CopyWordTo(Username(akun), currentWord);
//                 j++;
//             }
//             else if (currentChar == '\n' && j == 1)
//             {
//                 CopyWordTo(Password(akun), currentWord);
//                 j++;
//             }
//             else if (currentChar == '\n' && j == 2)
//             {
//                 if (WordEqual(*Password(akun),currentWord))
//                 {
//                     CopyWordTo(Bio(akun), emptyWord);
//                 }
//                 else
//                 {
//                     CopyWordTo(Bio(akun), currentWord);
//                 }
//                 j++;
//             }
//             else if (currentChar == '\n' && j == 3)
//             {
//                 if (WordEqual(*Bio(akun), currentWord) || WordEqual(*Password(akun),currentWord))
//                 {
//                     CopyWordTo(NoHP(akun), emptyWord);
//                 }
//                 else
//                 {
//                     CopyWordTo(NoHP(akun), currentWord);
//                 }
//                 j++;
//             }
//             else if (currentChar == '\n' && j == 4)
//             {
//                 if (WordEqual(*Bio(akun), currentWord) || WordEqual(*Password(akun),currentWord) || WordEqual(*NoHP(akun), currentWord))
//                 {
//                     CopyWordTo(Weton(akun), emptyWord);
//                 }
//                 else{
//                     CopyWordTo(Weton(akun), currentWord);
//                 }
//                 j++;
//             }
//             else if (currentChar == '\n' && j == 5)
//             {
//                 CopyWordTo(JenisAkun(akun), currentWord);
//                 j++;
//             }
//             else if (currentChar == '\n' && j > 5 && j < 11)
//             {
//                 //Foto Profil pengguna.config disini
//                 createMatrixchar(5, 10, &akun.fotoprofil);
//                 int k;
//                 for(k = 0; k < 10; k++){
//                     ELMTChar(akun.fotoprofil,j-6,k) = currentWord.TabWord[k*2];
//                 }
//                 j++;
//             }
//             ADVSENTENCE();
//         }
//         AddAccountToList(list, akun);
//     }
//     for(i = 0; i < N; i++)
//     {
//         for(j = 0; j < N; j++)
//         {
//             ELMTGRAF(*Teman,i,j) = CharToInt(currentWord.TabWord[j*2]);
//         }
//         ADVSENTENCE();
//     }
//     int countQ = WordToInt(currentWord);
//     if(countQ != 0)
//     {
//         for(i = 0; i < countQ-1; i++){
//             ADVSENTENCE();
//             teman temp;
//             for(j = 0; j < 3; j++){
//                 if(j == 0){
//                     temp.IDpengirim = CharToInt(currentWord.TabWord[j*2]);
//                 }
//                 if(j == 1){
//                     temp.IDpenerima = CharToInt(currentWord.TabWord[j*2]);
//                 }
//                 if(j == 2){
//                     temp.Jumlahteman = CharToInt(currentWord.TabWord[j*2]);
//                 }
//             }
//             Enqueueprio(Q, temp);
//         }
//         i = 0;
//         teman temp;
//         while (i < 5){
//             ADV();
//             if(i == 0){
//                 temp.IDpengirim = CharToInt(currentChar);
//             }
//             else if(i == 2){
//                 temp.IDpenerima = CharToInt(currentChar);
//             }
//             else if (i == 4){
//                 temp.Jumlahteman = CharToInt(currentChar);
//             }
//             i++;
//         }
//         Enqueueprio(Q, temp);
//     }
// }
// void loadTweetCnfg(char filename[],KicauList* kList){
//     int n;
//     STARTWORD_FILE(filename);
//     n = WordToInt(currentWord);
//     int j;
//     for (int i=0;i<n;i++){
//         Kicau k;
//         int id,like;
//         Word tex;
//         Word author;
//         time_t date;
//         j = 0;
//         while (j<5)
//         {
//             currentWord = emptyWord;
//             ADVSENTENCE();
//             if (j==0){
//                 id = WordToInt(currentWord);
//             }
//             else if (j==1) {
//                CopyWord(&tex,currentWord);
//             } 
//             else if (j==2){
//                 like = WordToInt(currentWord);
//             }
//             else if (j==3){
//                 CopyWord(&author,currentWord);
//             }else{
//                 struct tm tm = {0};
//                 strptime(currentWord.TabWord,"%d/%m/%Y %H:%M:%S",&tm);
//                 date = mktime(&tm);
//             }
//             j++;
//         }
//         CreateKicau(&k,author.TabWord);
//         k.id = id;
//         k.like = like;
//         copyWordToString(k.text,tex);
//         k.datetime = date;
//         AddKicauToList(k,kList);
//     }
// }

// void loadUtas(char filename[],KicauList* kList, int* jumlahUtas, AccountList akunList){
//     STARTWORD_FILE(filename);
//     int n = WordToInt(currentWord);
//     for (int i=0;i<n;i++){
//         ADVSENTENCE();
//         int id = WordToInt(currentWord);
//         int l;
//         Word user;
//         for (l = 0;l<kList->count && id!=kList->kicauan[l].id;l++){
            
//         }
       
//         CopyWordTo(&user,kList->kicauan[l].author);
//         int k;
//         for (k=0;k<akunList.count && !WordEqual(user,akunList.accounts[k].username[0]);k++){

//         }
//         Account akun = akunList.accounts[k];
//         ADVSENTENCE();
//         int jumlah = WordToInt(currentWord);
//         for (int j=0;j<jumlah;j++){
//             ADVSENTENCE();
//             kSambungAdd ksam = createKicauanSambung(currentWord,akun);
//             ADVSENTENCE();
//             ADVSENTENCE();
//             time_t date;
//             struct tm tm = {0};
//             strptime(currentWord.TabWord,"%d/%m/%Y %H:%M:%S",&tm);
//             date = mktime(&tm);
//             ksam->datetime = date;

//             kSambungAdd kPrev;
//             if (kList->kicauan[l].utasKicau==NULL){
//                 Utas u;
//                 u.IDUtas = *jumlahUtas+1;
//                 *jumlahUtas += 1;
//                 kList->kicauan[l].utasKicau = &u;
//                 kList->kicauan[l].utasKicau->content = ksam;
//             }else{
//                 kPrev = kList->kicauan[l].utasKicau->content;
//                 while (kPrev->next!=NULL)
//                 {
//                     kPrev = kPrev->next;
//                 }
//                 kPrev->next = ksam;
//             }
//         }
//     }
// }
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

// ///////////////////////////////////////////////////////////////////////////////////////////
// void saveUtas(char filename[],KicauList* kList, int jumlahUtas, AccountList akunList){
//     FILE *configFile = fopen(filename, "w");
//     fprintf(configFile,"%d\n",jumlahUtas);
//     for (int i=0;i<kList->count;i++){
//         if (kList->kicauan[i].utasKicau!=NULL){
//             fprintf(configFile,"%d\n",kList->kicauan[i].utasKicau->IDUtas);
//             kSambungAdd k = kList->kicauan[i].utasKicau->content;
//             int j = 1;
//             while (k->next!=NULL)
//             {
//                 j++;
//                 k = k->next;
//             }
//             fprintf(configFile,"%d",j);
//             k = kList->kicauan[i].utasKicau->content;
//             for (int n=0;n<j;n++){
//                 fprintf(configFile,"\ns\n",k->text);
//                 fprintf(configFile,"%s\n",k->author.TabWord);
//                 struct tm *tm_struct = localtime(&k->datetime);
//                 DATETIME local;
//                 CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
//                 int DD = Day(local);
//                 int MM = Month(local);
//                 int YY = Year(local);
//                 int hh = Hour(Time(local));
//                 int mm = Minute(Time(local));
//                 int ss = Second(Time(local));
//                 fprintf(configFile,"%02d/%02d/%d %02d:%02d:%02d", DD, MM, YY, hh, mm, ss);
//             }
            
//         }
//     }   
// }

// void saveTweet(char filename[],KicauList kList){
//     FILE *configFile = fopen(filename, "w");
//     fprintf(configFile,"%d",kList.count);
//     for (int i=0;i<kList.count;i++){
//         fprintf(configFile,"\n%d\n",kList.kicauan[i].id);
//         fprintf(configFile,"%s\n",kList.kicauan[i].text);
//         fprintf(configFile,"%d\n",kList.kicauan[i].like);
//         char * author;
//         copyWordToString(author,kList.kicauan[i].author);
//         fprintf(configFile,"%s\n",author);
//         struct tm *tm_struct = localtime(kList.kicauan[i].datetime);
//         DATETIME local;
//         CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);
//         int DD = Day(local);
//         int MM = Month(local);
//         int YY = Year(local);
//         int hh = Hour(Time(local));
//         int mm = Minute(Time(local));
//         int ss = Second(Time(local));
//         fprintf(configFile,"%02d/%02d/%d %02d:%02d:%02d", DD, MM, YY, hh, mm, ss);

//     }
// }
void SaveUser_FILE(char filename[], AccountList *list, Graf Teman, prioqueuefren Q)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL){
        fprintf(stderr, "Error opening file.\n");
    }
    fprintf(file, "%d\n", list->count);
    int i;
    for (i = 0; i < list->count; i++)
    {
        fprintf(file, "%s\n", list->accounts[i].username->TabWord);
        fprintf(file, "%s\n", list->accounts[i].password->TabWord);
        fprintf(file, "%s\n", list->accounts[i].bio->TabWord);
        fprintf(file, "%s\n", list->accounts[i].noHP->TabWord);
        fprintf(file, "%s\n", list->accounts[i].weton->TabWord);
        fprintf(file, "%s\n", list->accounts[i].jenisAkun->TabWord);
        int j;
        for(j = 0; j < 5; j++){
            int k;
            for(k = 0; k < 10; k++){
                fprintf(file, "%c", ELMTChar(list->accounts[i].fotoprofil,j,k));
                if (k != 9){
                    fprintf(file, " ");
                }
            }
            if (j != 4){
                fprintf(file, "\n");
            }
        }
        fprintf(file, "\n");
    }
    for (i = 0; i < list->count; i++){
        int j;
        for (j = 0; j < list->count; j++){
            fprintf(file, "%d", ELMTGRAF(Teman, i, j));
            if (j != list->count - 1){
                fprintf(file, " ");
            }
        }
        if (i != list->count - 1){
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");
    fprintf(file, "%d\n", NBElmtPrio(Q));
    int count = NBElmtPrio(Q);
    for (i = 0; i < count; i++)
    {
        teman temp;
        Dequeueprio(&Q, &temp);
        if (i == count-1){
            fprintf(file, "%d %d %d", temp.IDpengirim, temp.IDpenerima, temp.Jumlahteman);
        }
        else{
            fprintf(file, "%d %d %d\n", temp.IDpengirim, temp.IDpenerima, temp.Jumlahteman);
        }
    }
    fclose(file);
}

// void saveDraf(char filename[], AccountList *list, Stack *S){
    
// }