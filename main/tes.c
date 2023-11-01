#include "includeADT.h"
#include "functions.c"


int main() {
    AccountList list;
    CreateAccountList(&list);
    Graf temanl;
    createEmptyGraf(&temanl);    
    ReadUser_FILE("../cfg/pengguna.config", &list, &temanl);
    DisplayAccounts(&list);
    displayGraf(temanl, list.count);
}