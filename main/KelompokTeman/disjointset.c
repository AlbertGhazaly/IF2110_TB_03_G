#include "disjointset.h"

/**** Konstruktor ****/
DisjointSet makeDisjointSet(int length)
/* Membuat dan menginisialisasi himpunan disjoint dengan panjang tertentu.
    I.S.: length - panjang himpunan disjoint yang ingin dibuat.
    F.S.: DisjointSet yang telah diinisialisasi.
*/
{
    DisjointSet s;
    CreateListStatik(&s);

    for (int i = 0; i < length; i++) {
        ELMTSTAT(s, i) = MARKLISTGRAF;
    }
    return s;
}

/**** Finder ****/
int findIndexRoot(DisjointSet s,  int i)
/* Mencari indeks root dari suatu elemen.
    I.S.: s - DisjointSet yang ingin dicari rootnya.
          i - indeks elemen yang ingin dicari rootnya.
    F.S.: Indeks root dari elemen yang dicari.
*/
{
    while (ELMTSTAT(s, i) >= 0) {
        i = PARENT(s, i);
    }
    return i;
}


/**** Setter ****/
void UnionDisjointSet(DisjointSet *s, int i, int j)
/* Menggabungkan dua himpunan disjoint.
    I.S.: s - DisjointSet yang ingin digabungkan.
          i - indeks elemen pertama yang ingin digabungkan.
          j - indeks elemen kedua yang ingin digabungkan.
    F.S.: s - DisjointSet yang telah digabungkan.
*/
{
    int rootA = getIndexRoot(*s, i);
    int rootB = getIndexRoot(*s, j);

    boolean sameSet = (rootA == rootB);
    if (!sameSet) {
        if (ELMTSTAT(*s, rootA) <= ELMTSTAT(*s, rootB)) {
            ELMTSTAT(*s, rootA) += -1;
            ELMTSTAT(*s, rootB) = rootA;
        } else {
            ELMTSTAT(*s, rootA) = rootB;
            ELMTSTAT(*s, rootB) += -1;
        }
    }
}

DisjointSet findGroups(Graf m)
/* Mencari himpunan-himpunan disjoint dari suatu matriks graf.
    I.S.: m - matriks graf yang ingin dicari himpunan-himpunan disjointnya.
    F.S.: DisjointSet yang berisi himpunan-himpunan disjoint dari matriks graf.
*/
{
    int n = ROW_GRAF;

    DisjointSet s = makeDisjointSet(n);
    for (int i = 0; i < n; i++) {
        for (int j = (i + 1); j < n; j++) {
            if (ELMT_MATRIXCHAR(m, i, j) == 1) {
                UnionDisjointSet(&s, i, j);
            }
        }
    }
    return s;
}