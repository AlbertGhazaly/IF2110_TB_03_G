#include "SimpanMuat.h"
#include <sys/stat.h>

void muat(char floderName[]){
    char path[] = "../cfg/";

    if (!isDirExist(concatStr(path,floderName))){
        printf("Tidak ada folder yang dimaksud!\n");
    }else{
        for (int i=0;i<5;i++){
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
