#ifndef DrafKicauan_H
#define DrafKicauan_H

#include "../../modules/adt.h"
#include "../Pengguna/Pengguna.h"

Stack* createSTackDrafPerUser(Stack S);

void buatdraf(Stack *draf, int userID, AccountList *list);

void lihatdraf(Stack *draf, int userID, AccountList *list);

#endif
