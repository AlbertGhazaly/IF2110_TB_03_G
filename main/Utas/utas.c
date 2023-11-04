#include "utas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
Word iya = {"IYA",3};
Word tidak = {"TIDAK",5};

void createUtas(int id, KicauList* kList, Account account, int jumlahUtas){

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
                kSambungAdd kSam = createKicauanSambung(currentWord,account);
                kicau->utas.content = kSam;
                jumlahUtas++;
                kicau->utas.IDUtas = jumlahUtas;
                printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK) ");
                STARTWORD();
                if (!lanjut){
                    isStop = true;
                }else{
                    isStop = false;
                }
                while (!isStop)
                {
                    printf("Masukkan kicauan:\n");
                    STARTSENTENCE();
                    kSam->next = createKicauanSambung(currentWord,account);
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

void sambungUtas(int idUtas, KicauList* kList,int index, Account account){
    boolean isFound = false;
    Kicau* kicauan;
    for (int i=0;(i<kList->count) && (!isFound);i++){
        if (kList->kicauan[i].utas.IDUtas == idUtas){
            isFound = true;
            *kicauan = kList->kicauan[i];
        }
    }
    if (!isFound){
        printf("Utas tidak ditemukan!\n");
    }else{
        if (!WordEqual(kicauan->author,account.username[0])){
            printf("Anda tidak bisa menyambung utas ini!\n");
        }else{
            int i =1;
            kSambungAdd kSam= kicauan->utas.content;
            while (kSam->next!=NULL)
            {
                i++;
                kSam = kSam->next;
            }
            
            if (index<1){
                printf("Index terlalu rendah!\n");
            }else if (index>i+1){
                printf("Index terlalu tinggi!\n");
            }else{
                printf("Masukkan kicauan:\n");
                STARTSENTENCE();
                kSam = kicauan->utas.content;
                kSambungAdd newKSam = createKicauanSambung(currentWord,account);
                if (index==1){
                    newKSam->next = kSam;
                    kicauan->utas.content = newKSam;
                }else{
                    for (int j=2;j<index;j++){
                       kSam = kSam->next;
                    }
                    if ((kSam->next)==NULL){
                        kSam->next = newKSam;
                    }else{
                        newKSam->next = kSam->next;
                        kSam->next = newKSam;
                    }
                }

            }
        }

    }


}

void hapusUtas(int idUtas, int index, Account account);

kSambungAdd createKicauanSambung(Word tex, Account account){
    kSambungAdd kicauSam = (kSambungAdd)malloc(sizeof(KicauSambung));
    if (kicauSam!=NULL){
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
