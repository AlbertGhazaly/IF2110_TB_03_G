/* File : tree.h */
/* ADT pohon N-Ary */
/* Representasi Address dengan pointer */
/* ElType adalah Makanan */

#include "tree.h"

Address NewTreeNode(Infotype root)
/* Mengalokasikan sebuah Address t, bernilai Nal jika tidak berhasil */
/* Mengirimkan Address hasil alokasi sebuah elemen bernilai root
   Jika alokasi berhasil, maka Address tidak Nal dan menghasilkan t
   ROOT(t) = val, SUBADDRESS(t) terdefinisi dengan ukuran INITIAL,
   TREECOUNT(t) = 0, dan TREECAPACITY(t) = INITIAL 
   Jika alokasi gagal, maka mengirimkan Nal */
{
	Address t = (Address) malloc(sizeof(NodeTree));

	if (t != Nal) 
	{
		ROOT(t) = root;
		SUBADDRESS(t) = (Address*) malloc(INITIAL * sizeof(Address*));
		TREECOUNT(t) = 0;
		TREECAPACITY(t) = INITIAL;
	}

	return t;
}

Tree NewTree(Infotype root, Tree child)
/* Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   dan TREECOUNT bertambah satu jika child bukan Nal */
/* Jika alokasi gagal, menghasilkan pohon kosong (Nal) */
{
	Address t = NewTreeNode(root);
	if (t != Nal)
	{
		SUBTREE(t, TREECOUNT(t)) = child;

		if (child != Nal)
			TREECOUNT(t)++;
	}
	return t;
}

void CreateTree(Infotype root, Tree child, Tree *t)
/* I.S. : Sembarang
   F.S. : Menghasilkan sebuah pohon t
   		  Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   		  dan TREECOUNT bertambah satu jika child bukan Nal
   		  Jika alokasi gagal, menghasilkan pohon kosong (Nal) */
{
	*t = NewTreeNode(root);
	if (*t != Nal)
	{
		SUBTREE(*t, TREECOUNT(*t)) = child;

		if (child != Nal)
			TREECOUNT(*t)++;
	}
}

void insertTree(Tree *t, int ID, Infotype balasan)
{
    boolean check = false;
    Tree t = NewTree(balasan, Nal);

    
}

void insertTreeRecursion(Tree t , int parentID, Tree child, boolean * found){
    if (t != Nal){
       int i = 0;
       if (ROOT(t).id == parentID){
            *found = true;
            ConnectChild(child, &t);
        }
        while(i < TREECOUNT(t) && !(*found)){
            insertTreeRecursion(SUBTREE(t,i), parentID, child, found);
            i++;
        }
    }
}

void deleteTree(Tree *t, int ID){
    boolean found = false;
    deleteTreeRecursion(t, ID, &found);
}

void deleteTreeRecursion(Tree *t, int ID, boolean * found){
    if (t != Nal){
       int i = 0;
       if (ROOT(*t).id == ID){
            *found = true;
            *t = Nal;
        }
        while(!(*found) && i < TREECOUNT(*t)){
            deleteTreeRecursion(&SUBTREE(*t,i), ID, found);
            i++;
        }
    }
}

void ConnectChild(Tree child, Tree *t)
/* I.S. : t dan child terdefinisi
   F.S. : t terhubung dengan child dan TREECOUNT bertambah satu jika child bukan Nal */
{
	if (TREECOUNT(*t) == TREECAPACITY(*t))
		ExpandCapacity(t);

	SUBTREE(*t, TREECOUNT(*t)) = child;

	if (child != Nal)
		TREECOUNT(*t)++;
}

void ConnectParent(Tree parent, Tree *t)
/* I.S. : t dan parent terdefinisi
	F.S. : t menjadi child dari parent, ROOT(t) menjadi ROOT(parent) */
{
	ConnectChild(*t, &parent);

	*t = parent;
}

void DeallocateTree(Address t)
/* I.S. : t terdefinisi
   F.S. : t dikembalikan ke sistem
   Melakukan dealokasi/pengembalian Address t */
{
	free(t);
}

boolean HasNoChild(Tree t)
/* Mengirimkan true jika t tidak memiliki child */
{
	if (TREECOUNT(t) == 0)
		return true;
	return false;
}

boolean HasOneChild(Tree t)
/* Mengirimkan true jika t hanya memiliki 1 child */
{
	if (TREECOUNT(t) == 1)
		return true;
	return false;
}

/***** Display Tree *****/
void PrintTree(Tree t)
/* I.S. : t terdefinisi
   F.S. : Semua simpul t sudah dicetak secara preorder: root dan child(ren)
   		  Setiap pohon ditandai dengan tanda kurung buka dan tanda kurung tutup ()
   		  Pohon kosong ditandai dengan () */
{
	if (t == Nal)
	{
		printf("()");
	}
	else
	{
		printf("(");
		printf("%d", ROOT(t));
		int i;
		for (i = 0; i < TREECOUNT(t); i++)
			PrintTree(SUBTREE(t,i));
		printf(")");
	}
}

void ExpandCapacity(Tree *t)
/* Proses: Memperbesar dua kali lipat capacity t */
/* I.S. : t terdefinisi */
/* F.S. : Ukuran SubTree menjadi dua kali lipat ukuran semula */
{
	TREECAPACITY(*t) *= 2;

	Address *temp = SUBADDRESS(*t);

	SUBADDRESS(*t) = (Address*) malloc(TREECAPACITY(*t) * sizeof(Address*));
	TREECOUNT(*t) = 0;
	
	int i;
	for (i = 0; i < TREECAPACITY(*temp); i++)
		SUBTREE(*t,i) = SUBTREE(*temp,i);
}

void searchTree(Tree t, int parentID){
    boolean found = false;
    searchTreeRecursion(t, parentID, &found);
    return found;
}

void searchTreeRecursion(Tree t, int parentID, boolean * found){
    if (t != Nal){
       int i = 0;
       if (ROOT(t).id == parentID){
            *found = true;
        }
        while(!(*found) && i < TREECOUNT(t)){
            searchTreeRecursion(SUBTREE(t,i), parentID, found);
            i++;
        }
    }
}
