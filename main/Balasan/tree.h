/*tree.h*/
/* tree berbentuk n-ary dengan infotype kicauan */

#ifndef TREE_H
#define TREE_H

#include "../../modules/adt.h"

typedef struct {
    int id;
    char text[281];
    Word author;
    DATETIME datetime;
} Balasan;


/* Selektor */
#define ROOT(t) (t)->T
#define SUBADDRESS(t) (t)->SubTree
#define SUBTREE(t,n) (t)->SubTree[n]
#define TREECOUNT(t) (t)->Count
#define TREECAPACITY(t) (t)->Capacity

#define Nal NULL
#define INITIAL 5

typedef Balasan Infotype;
typedef struct TNode *Address;
typedef struct TNode
{
	Infotype T;
	Address *SubTree;
	int Count;
	int Capacity;
} NodeTree;

typedef Address Tree;

Address NewTreeNode(Infotype root);
/* Mengalokasikan sebuah Address t, bernilai Nil jika tidak berhasil */
/* Mengirimkan Address hasil alokasi sebuah elemen bernilai root
   Jika alokasi berhasil, maka Address tidak Nil dan menghasilkan t
   ROOT(t) = val, SUBADDRESS(t) terdefinisi dengan ukuran INITIAL,
   COUNT(t) = 0, dan TREECAPACITY(t) = INITIAL 
   Jika alokasi gagal, maka mengirimkan Nil */

Tree NewTree(Infotype root, Tree child);
/* Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   dan count bertambah satu jika child bukan Nil */
/* Jika alokasi gagal, menghasilkan pohon kosong (Nil) */

void CreateTree(Infotype root, Tree child, Tree *t);
/* I.S. : Sembarang
   F.S. : Menghasilkan sebuah pohon t
   		  Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   		  dan count bertambah satu jika child bukan Nil
   		  Jika alokasi gagal, menghasilkan pohon kosong (Nil) */

void insertTree(Tree *t, int ID, Infotype balasan);

void insertTreeRecursion(Tree *t, int ID, Infotype balasan, boolean * found);

void deleteTree(Tree *t, int ID);

void deleteTreeRecursion(Tree *t, int ID, boolean * found);

void ConnectChild(Tree child, Tree *t);
/* I.S. : t dan child terdefinisi
   F.S. : t terhubung dengan child dan count bertambah satu jika child bukan Nil */

void ConnectParent(Tree parent, Tree *t);
/* I.S. : t dan parent terdefinisi
   F.S. : t menjadi child dari parent, ROOT(t) menjadi ROOT(parent) */

void DeallocateTree(Address t);
/* I.S. : t terdefinisi
   F.S. : t dikembalikan ke sistem
   Melakukan dealokasi/pengembalian Address t */

boolean HasNoChild(Tree t);
/* Mengirimkan true jika t tidak memiliki child */

boolean HasOneChild(Tree t);
/* Mengirimkan true jika t hanya memiliki 1 child */

/***** Display Tree *****/
void PrintTree(Tree t);
/* I.S. : t terdefinisi
   F.S. : Semua simpul t sudah dicetak secara preorder: root dan child(ren)
   		  Setiap pohon ditandai dengan tanda kurung buka dan tanda kurung tutup ()
   		  Pohon kosong ditandai dengan () */

void ExpandCapacity(Tree *t);
/* Proses: Memperbesar dua kali lipat TREECAPACITY t */
/* I.S. : t terdefinisi */
/* F.S. : Ukuran SubTree menjadi dua kali lipat ukuran semula */

void searchTreeRecursion(Tree t, int parentID, boolean * found);

#endif