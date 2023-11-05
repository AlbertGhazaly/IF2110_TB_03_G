#ifndef Kicauan_H
#define Kicauan_H

#include "../../modules/adt.h"

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

#endif