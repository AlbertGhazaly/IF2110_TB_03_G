#include <stdio.h>
#include "Kicauan.h"
#include "../../modules/wordmachine/charmachine.h"
#include "../../modules/wordmachine/wordmachine.h"
#include "../../modules/time/datetime.h"
#include "../../modules/time/time.h"

int main () 
{
    Account User;
    CreateAccount(&User, {}, "user");

    ListKicau L;
    CreateListKicau(&L);
    Kicau k;
    CreateKicau(&k, author);
    AddKicauToList(k, &L);
    Kicauan(L);
}