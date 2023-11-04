#include "utas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void createUtas(int id, KicauList* kList, Account account);

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
