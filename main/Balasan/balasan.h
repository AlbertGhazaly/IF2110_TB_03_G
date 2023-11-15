#ifndef BALASAN_H
#define BALASAN_H

#include "../boolean.h"
#include "../../modules/adt.h"
#include <time.h>

#define MAXChar 280

/* Definisi Type Data */
typedef struct tNode *addressTree;
typedef struct tNode {
    int data;
    addressTree firstChild;
    addressTree nextSibling;
} Node;

typedef struct {
    addressTree root;
} Tree;

typedef Tree ListTreeStatik_ElType;
typedef int ListTreeStatik_IdxType;
typedef struct {
    ListTreeStatik_ElType contents[CAPACITY]; /* memori tempat penyimpan elemen (container) */
} ListTreeStatik;

#define Data(P) (P)->data
#define FirstChild(P) (P)->firstChild
#define NextSibling(P) (P)->nextSibling
#define Root(T) (T).root
#define LISTELMT(l, i) (l).contents[(i)]

typedef struct kicau {
    int id;
    char text[MAXChar];
    Word author;
    time_t datetime;
    Tree kumpulanBalasan;  
 } Balasan;

void CreateBalasan(Balasan *balasan, Account author);
void MembalasKicauan(Tree *balasanKicauan, Balasan *balasan, int balasanId);
void MembalasBalasan(Tree *balasanKicauan, Balasan *balasan, int parentId);
void DisplayBalasan(Tree balasanKicauan, int balasanId);
void DeleteBalasan(Tree *balasanKicauan, int balasanId);
void PrintBalasan(Balasan balasan);
void CascadeDelete(Tree *balasanKicauan, int parentId);

#endif