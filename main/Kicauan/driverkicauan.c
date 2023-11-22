#include <stdio.h>
#include "Kicauan.h"

int main () 
{
    Account User;
    AccountList listakun;
    CreateAccountList(&listakun);

    signup(&listakun);
    printf("selesai"); //ini buat ngetes doang

    ListKicau L;
    CreateListKicau(&L); //bikin empty list dinamis 
    Kicau k;
    CreateKicau(User, &L, &k); //ini bikin kicauan + input text dari user
    Kicauan(User, L); //ini ngeprint kicauan
}