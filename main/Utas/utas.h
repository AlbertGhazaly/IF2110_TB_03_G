#include "../modules/adt.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXChar 280

typedef struct kicau {
    int id;
    int like;
    char text[MAXChar];
    Word author;
    time_t datetime;
    Utas* utas;
} Kicau;

typedef struct {
    Kicau kicauan[1000];
    int count;
} KicauList;

typedef struct kicausambung *kSambungAdd;
typedef struct kicausambung {
    int index;
    char text[MAXChar];
    time_t datetime;
    Word author;
    kSambungAdd next;

} KicauSambung;

typedef struct{
    int IDUtas;
    kSambungAdd content;
} Utas;

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_BIO_LENGTH 135
#define MAX_HP_LENGTH 100
#define MAX_WETON_LENGTH 50
#define MAX_JENIS_LENGTH 50
#define MARKACC '\0'

typedef struct {
    Word username[MAX_USERNAME_LENGTH];
    Word password[MAX_PASSWORD_LENGTH];
    Word bio[MAX_BIO_LENGTH];
    Word noHP[MAX_HP_LENGTH];
    Word weton[MAX_WETON_LENGTH];
    Word jenisAkun[MAX_JENIS_LENGTH];
    MatrixChar fotoprofil;
} Account;

#define Username(U) (U).username
#define Password(U) (U).password
#define Bio(U) (U).bio
#define NoHP(U) (U).noHP
#define Weton(U) (U).weton
#define JenisAkun(U) (U).jenisAkun

void sambungUtas(int idUtas, int index, Account account);
void createUtas(int id, KicauList* list, Account account);
void hapusUtas(int idUtas, int index, Account account);
kSambungAdd createKicauanSambung(Word tex, Account account, int index);
boolean lanjut(Word input);
