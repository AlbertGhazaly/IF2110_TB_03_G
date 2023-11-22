#ifndef SimpanMuat_H
#define SimpanMuat_H
#include "../Pengguna/Pengguna.h"
#include "../Kicauan/Kicauan.h"
#include "../../modules/adt.h"
#define MAXChar 281
char* concatStr(char path[],char folder[]);
boolean isDirExist(char path[]);
void ReadUser_FILE(char filename[], AccountList *list, Graf *Teman, prioqueuefren *Q);

#endif