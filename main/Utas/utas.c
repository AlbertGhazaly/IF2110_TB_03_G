#include "utas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
Word iya = {"IYA",3};
Word tidak = {"TIDAK",5};

void createUtas(int id, KicauList* kList, Account account){

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
            if (kicau->utas!=NULL){
                printf("Kicauan ini telah digunakan utas lain!\n");
            }else{
                boolean isStop = false;
                printf("Utas berhasil dibuat!\n");
                printf("Masukkan kicauan: \n");
                STARTSENTENCE();
                kSambungAdd kSam = createKicauanSambung(currentWord,account,1);
                kicau->utas = kSam;
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                STARTWORD();
                if (!lanjut){
                    isStop = true;
                }else{
                    isStop = false;
                }
                int i=2;
                while (!isStop)
                {
                    printf("Masukkan kicauan:\n");
                    STARTSENTENCE();
                    kSam->next = createKicauanSambung(currentWord,account,i);
                    i++;
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

void sambungUtas(int idUtas, int index, Account account);

void hapusUtas(int idUtas, int index, Account account);

kSambungAdd createKicauanSambung(Word tex, Account account, int index){
    kSambungAdd kicauSam = (kSambungAdd)malloc(sizeof(KicauSambung));
    if (kicauSam!=NULL){
        kicauSam->index = index;
        kicauSam->next = NULL;
        CopyWordTo(&kicauSam->text,tex);
        CopyWordTo(&kicauSam->author,account.username[0]);
        kicauSam->datetime = time(NULL);
    }
    return kicauSam;
}
boolean lanjut(Word input){
    if (WordEqual(input,iya)){
        return true;
    }else if (WordEqual(input, tidak)){
        return false;
    }else{
        STARTWORD();
        lanjut(currentWord);
    }
}
