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
    int i;
    char path[] = "../cfg/";
    for (i=0;path[i]!='\0';i++);
    for (int j=0;folderName[j]!='\0';j++){
        path[i] = folderName[j];
        i++;
    }
    path[i] = '\0';


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