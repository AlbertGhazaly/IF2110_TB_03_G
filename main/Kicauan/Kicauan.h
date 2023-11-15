#ifndef KICAUAN_H
#define KICAUAN_H

#include "../../modules/adt.h"
#include <time.h>
#define MAXChar 280

typedef struct {
    int id;
    int like;
    char text[MAXChar];
    Word author;
    DATETIME datetime;
} Kicau;

typedef struct {
    Kicau* kicau;
    int Cap;
    int nEff;
} ListKicau;

int CreateIDKicau(ListKicau *list);
void AddToKicauan(ListKicau *list, Kicau k);
void CreateKicau(ListKicau *list, Kicau *k);
void BaseDisplay (Kicau k);
void Kicauan(ListKicau list);
void SukaKicau (int id, ListKicau *listkicau, Kicau *k, AccountList* listakun, Graf teman);
void UbahKicau (int id, ListKicau *list);

#endif