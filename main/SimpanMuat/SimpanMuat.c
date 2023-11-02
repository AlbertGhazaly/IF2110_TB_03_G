#include "SimpanMuat.h"
#include <sys/stat.h>

void muat(char floderName[]){

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

void simpan(char folderName[]){
    // concat path to cfg folder
    char path[]= "../cfg/";
    if (!isDirExist(concat(path,folderName))){
        printf("Belum terdapat Folder1.\nAkan dilakukan pembuatan Folder1 terlebih dahulu.");
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
char* concat(char path[],char folder[]){
    int i;
    for (i=0;path[i]!='\0';i++);
    for (int j=0;folder[j]!='\0';j++){
        path[i] = folder[j];
        i++;
    }
    path[i] = '\0';
    return path;
}