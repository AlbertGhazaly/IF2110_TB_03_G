#include "Teman.h"

void daftarteman(boolean login, Account akunlogin, AccountList* listakun, Graf teman)
{
    ListGraf l;
    CreateListGraf(&l);
    if (login)
    {
        int idAkun;
        int i = 0;
        boolean found = false;
        while(i < listakun->count && found == false)
        {
            if(WordEqual(*listakun->accounts[i].username, *akunlogin.username))
            {
                idAkun = i;
                found = true;
            }
            i++; 
        }
        getOne(teman,idAkun,&l);
        if (isEmptylistGraf(l))
        {
            printf("%s belum mempunyai teman\n", akunlogin.username);
        }
        else{
            printf("%s memiliki %d teman\n", akunlogin.username, listEffGraf(l));
            printf("Daftar teman %s\n", akunlogin.username);
            int i;
            for (i = 0; i < CAPACITYGRAF; i++)
            {
                if (ELMTLISTGRAF(l,i) == 1)
                {
                    printf("| %s\n", listakun->accounts[i].username);
                }
            }
        }
    }
    else{
        printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
    }
}