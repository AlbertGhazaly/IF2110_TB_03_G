#ifndef DrafKicauan_H
#define DrafKicauan_H

#include "../../modules/adt.h"
#include "../Pengguna/Pengguna.h"

Stack* createSTackDrafPerUser(Stack S);

void buatdraf(Stack drafStack[], int userID, AccountList *list);

void lihatdraf(Stack drafStack[], int userID, AccountList *list);


#endif
