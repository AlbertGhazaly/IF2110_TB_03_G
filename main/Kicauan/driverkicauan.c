#include <stdio.h>
#include "kicauan.h"
#include "../../modules/wordmachine/charmachine.h"
#include "../../modules/wordmachine/wordmachine.h"
#include "../../modules/time/datetime.h"
#include "../../modules/time/time.h"

int main () 
{
    KicauList L;
    Kicau k;

    CreateKicauList(&L);

    char author[] = "John Doe";
    CreateKicau(&k, author);
    AddKicauToList(k, &L);
    Kicauan(&L);
}