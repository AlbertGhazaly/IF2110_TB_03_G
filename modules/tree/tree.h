#ifndef TREE_H
#define TREE_H

#include "../boolean.h"
#include "../../modules/adt.h"
#include <time.h>

/* Definisi Type Data */
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

#endif