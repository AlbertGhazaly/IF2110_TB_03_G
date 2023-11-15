#ifndef Kicauan_H
#define Kicauan_H

#include "../../modules/adt.h"
#include "Pengguna/Pengguna.h"

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
#define MAXChar 280

typedef struct kicau {
    int id;
    int like;
    char text[MAXChar];
    Word author;
    time_t datetime;
    Utas* utasKicau;
 } Kicau;
 
typedef struct {
    Kicau kicauan[1000];
    int count;
} KicauList;

void CreateKicau (Kicau *k, char author[]);

void BaseDisplay (Kicau k);

void DisplayKicau (Kicau k);

void CreateKicauList(KicauList *list);

void AddKicauToList (Kicau k, KicauList *list);

void Kicauan (KicauList *list);

void SukaKicau (Account akunLogin, int id, KicauList *list, Kicau *k, AccountList* listakun, Graf teman);

boolean isIdInKicauan (int id, KicauList *list);

void UbahKicau (Account akunLogin, int id, KicauList *list);

#endif