#include "includeADT.h"
#include "functions.c"


int main() {
    AccountList list;
    CreateAccountList(&list);
    Matrix temanl;    
    ReadUser_FILE("../cfg/pengguna.config", &list, &temanl);
    DisplayAccounts(&list);
}