#include "../../modules/adt.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Kicauan/Kicauan.h"
#include "../Pengguna/Pengguna.h"
#define MAXChar 280

typedef struct kicausambung *kSambungAdd;
typedef struct kicausambung {
    int index;
    char text[MAXChar];
    time_t datetime;
    Word author;
    kSambungAdd next;

} KicauSambung;

typedef struct {
    int IDUtas;
    kSambungAdd content;
} Utas;

void sambungUtas(int idUtas,int index, KicauList* kList, Account account);
void createUtas(int id, KicauList* list, Account account, int* jumlahUtas);
void hapusUtas(int idUtas, int index,KicauList* kList ,Account account);
void cetakUtas(int idUtas, KicauList kList,Account account, AccountList listAccount,Graf teman);
kSambungAdd createKicauanSambung(Word tex, Account account);
boolean lanjut(Word input);
void copyWordToString(char (destination[MAXChar]),Word input);