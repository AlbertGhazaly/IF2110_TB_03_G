#ifndef Disjointset_H
#define Disjointset_H

#define PARENT(s, i) (ELMTSTAT(s, i))

#include "../../modules/adt.h"

typedef ListStatik DisjointSet;

/**** Konstruktor ****/
DisjointSet makeDisjointSet(int length);
/* Membuat dan menginisialisasi himpunan disjoint dengan panjang tertentu.
    I.S.: length - panjang himpunan disjoint yang ingin dibuat.
    F.S.: DisjointSet yang telah diinisialisasi.
*/

/**** Finder ****/
int findIndexRoot(DisjointSet s,  int i);
/* Mencari indeks root dari suatu elemen.
    I.S.: s - DisjointSet yang ingin dicari rootnya.
          i - indeks elemen yang ingin dicari rootnya.
    F.S.: Indeks root dari elemen yang dicari.
*/

/**** Setter ****/
void UnionDisjointSet(DisjointSet *s, int i, int j);
/* Menggabungkan dua himpunan disjoint.
    I.S.: s - DisjointSet yang ingin digabungkan.
          i - indeks elemen pertama yang ingin digabungkan.
          j - indeks elemen kedua yang ingin digabungkan.
    F.S.: s - DisjointSet yang telah digabungkan.
*/

DisjointSet findGroups(Graf m);
/* Mencari himpunan-himpunan disjoint dari suatu matriks graf.
    I.S.: m - matriks graf yang ingin dicari himpunan-himpunan disjointnya.
    F.S.: DisjointSet yang berisi himpunan-himpunan disjoint dari matriks graf.
*/

#endif