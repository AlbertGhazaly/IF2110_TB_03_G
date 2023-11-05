#include "../../modules/adt.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Pengguna/Pengguna.h"
#include "../Kicauan/Kicauan.h"

void sambungUtas(int idUtas,int index, KicauList* kList, Account account);
void createUtas(int id, KicauList* list, Account account, int* jumlahUtas);
void hapusUtas(int idUtas, int index,KicauList* kList ,Account account);
void cetakUtas(int idUtas, KicauList kList,Account account, AccountList listAccount,Graf teman);
kSambungAdd createKicauanSambung(Word tex, Account account);
boolean lanjut(Word input);
void copyWordToString(char (destination[MAXChar]),Word input);