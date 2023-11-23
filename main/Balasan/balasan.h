#ifndef BALASAN_H
#define BALASAN_H

#include "../../modules/adt.h"
#include <time.h>

#define MAXChar 280
typedef struct kicau {
    int id;
    char text[MAXChar];
    Word author;
    DATETIME datetime;
    Tree kumpulanBalasan;  
 } Balasan;

#define ROOT(t) (t)->T
#define SUBADDRESS(t) (t)->SubTree
#define SUBTREE(t,n) (t)->SubTree[n]
#define TREECOUNT(t) (t)->Count
#define TREECAPACITY(t) (t)->Capacity

#define Nal NULL
#define INITIAL 5

typedef struct tNode *addressTree;
typedef struct tNode {
    int data;
    addressTree firstChild;
    addressTree nextSibling;
} NodeTree;

typedef struct {
    addressTree root;
} Tree;

typedef Tree ListTreeStatik_ElType;
typedef int ListTreeStatik_IdxType;
typedef struct {
    ListTreeStatik_ElType contents[CAPACITY]; 
} ListTreeStatik;


#define Data(P) (P)->data
#define FirstChild(P) (P)->firstChild
#define NextSibling(P) (P)->nextSibling
#define Root(T) (T).root
#define LISTELMT(l, i) (l).contents[(i)]


void CreateTree(Tree *T);

addressTree Alokasi(int X);

void Dealokasi(addressTree P);

void AddChild(addressTree *P, addressTree C);

void AddSibling(addressTree *P, addressTree S);

void printSiblings(addressTree P);

void printChild(addressTree P);

void printTree (addressTree P, int h);

addressTree getAddress (addressTree P, int X);

addressTree getParent(addressTree root,addressTree C);

void CreateBalasan(Balasan *balasan, Account author);
void BaseDisplayTree (Balasan b);
void MembalasKicauan(Tree *balasanKicauan, Balasan *balasan, int balasanId);
void MembalasBalasan(Tree *balasanKicauan, Balasan *balasan, int parentId);
void DisplayBalasan(Tree balasanKicauan, int balasanId);
void DeleteBalasan(Tree *balasanKicauan, int balasanId);
void CascadeDelete(Tree *balasanKicauan, int parentId);

#endif