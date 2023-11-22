#ifndef KICAUAN_H
#define KICAUAN_H

#include "../../modules/adt.h"
#include "../Pengguna/Pengguna.h"
#include <time.h>
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

typedef struct {
    int id;
    int like;
    char text[MAXChar];
    Word author;
    DATETIME datetime;
    Utas* utasKicau;
} Kicau;

typedef struct {
    Kicau* kicau;
    int Cap;
    int nEff;
} ListKicau;

ListKicau CreateListKicau(ListKicau *list);
int CreateIDKicau(ListKicau *list);
void AddToKicauan(ListKicau *list, Kicau k);
void CreateKicau(Account akunLogin, ListKicau *list, Kicau *k);
void BaseDisplay (Kicau k);
void Kicauan(Account akunLogin, ListKicau list);
void SukaKicau (Account akunLogin, int id, ListKicau *listkicau, Kicau *k, AccountList* listakun, Graf teman);
boolean isIdInKicauan (int id, ListKicau *list);
void UbahKicau (Account akunLogin, int id, ListKicau *list);

#endif