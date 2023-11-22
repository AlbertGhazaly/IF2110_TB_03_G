#ifndef Teman_H
#define Teman_H

#include "../../modules/adt.h"
#include "../Pengguna/Pengguna.h"

void daftarteman(boolean login, Account akunlogin, AccountList* listakun, Graf teman);

void hapusteman(boolean login, Account akunlogin, AccountList* listakun, Graf* teman);

#endif