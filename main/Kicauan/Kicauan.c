#include "Kicauan.h"
#include "../../modules/adt.h"
#include "Pengguna/Pengguna.h"
#include <stdio.h>
#include <string.h>

Word publik = {"publik" , 6};

ListKicau CreateListKicau(ListKicau *list)
{
    list->nEff = 0;
    list->Cap = 100;
    list->kicau = (Kicau*) malloc(list->Cap * sizeof(Kicau));
    return *list;
}

int CreateIDKicau(ListKicau *list) {
    if (list->nEff == 0) 
    {
        return 1;
    } 
    else 
    {
        return list->kicau[list->nEff - 1].id + 1;
    }
}

void AddToKicauan(ListKicau *list, Kicau k) {
    list->kicau[list->nEff] = k;
    list->nEff++;
}

void CreateKicau(Account akunLogin, ListKicau *list, Kicau *k) {
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    DATETIME local;
    CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);

    //baca text kicauan
    int el = 0;
    printf("Masukkan kicauan:\n");
    START();

    while (el < MAXChar)
    {
        if (currentChar == ';')
        {
            break;
        }
        k->text[el] = currentChar;
        el++;
        ADV();
    }
    k->text[el] = '\0';


    k->id = CreateIDKicau(list); 
    k->like = 0;
    CopyWordTo(akunLogin.username, k->author);
    k->datetime = local;
    k->utasKicau = NULL;
    printf("Selamat! Kicauan telah diterbitkan!\n Detil kicauan:\n");
    BaseDisplay(*k);
    AddToKicauan(list, *k);
}

void BaseDisplay (Kicau k)
{
    printf("\n| ID = %d\n", k.id);

    //print author (without length seperti di ADT)
    printf("| ");
    int i;
    for (i = 0; i < k.author.Length; i++) 
    {
        printf("%c", k.author.TabWord[i]);
    }
    printf("\n");

    //print time upload kicauan
    printf("| ");
    TulisDATETIME(k.datetime);
    printf("\n");

    //print text
    int j = 0;
    printf("| ");
    while (k.text[j] != '\0')
    {
        printf("%c", k.text[j]);
        j++;
    }

    //print likes
    printf("\n| Disukai: %d\n\n", k.like);
}

void Kicauan(Account akunLogin, ListKicau list) {
    //Print Kicauan (list kicau)
    for (int i = list.nEff - 1; i >= 0; i--) {
        if (isEqualWord(list.kicau[i].author.TabWord, akunLogin.username)) {
            BaseDisplay(list.kicau[i]);
        }
    }
}

void SukaKicau (Account akunLogin, int id, ListKicau *listkicau, Kicau *k, AccountList* listakun, Graf teman)
{
    //Account ID user saat ini
    int id_user = GetAccountIdx(listakun, akunLogin);

    //Account ID username penulis kicauan yang ingin di-like
    int i = 0;
    boolean found = false;
    while (!found && i < listkicau->nEff) {
        if (WordEqualAccount(*listakun->accounts[i].username, listkicau->kicau[k->id].author)) {
            found = true;
        }
        i++;
    }
    int id_penulis = i-1;

    if (id > listkicau->nEff)
    {
        printf("Tidak ditemukan kicauan dengan ID = %d;", id);
    }
    else
    {
        //Jika dua akun berteman
        if(WordEqual(*listakun->accounts[id_penulis].jenisAkun, publik) || ELMTGRAF(teman, id_user, id_penulis))
        {
            listkicau->kicau[k->id].like++;
            printf("Selamat! kicauan telah disukai!\nDetil kicauan:");
            BaseDisplay(listkicau->kicau[id]);
        }
        else
        {
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya");
        }
    }
}

boolean isIdInKicauan (int id, ListKicau *list)
{
    if (id > list->nEff)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < list->nEff; i++)
        {
            if (list->kicau[id].id == 0)
            {
                return false;
            }
        }
        return true;
    }
}

void UbahKicau (Account akunLogin, int id, ListKicau *list) 
{
    if (!isIdInKicauan(id, list))
    {
        printf("Tidak ditemukan kicauan dengan ID = %d!", id);
    }
    else
    {
        if (!WordEqual(list->kicau[id].author, *akunLogin.username))
        {
            printf("Kicauan dengan ID = %d bukan milikmu!", id);
        }
        else
        {
            printf("Masukkan kicauan baru:\n");
            START();
            int el = 0;
            while (el < MAXChar)
            {
                if (currentChar == ';')
                {
                    break;
                }
                list->kicau[id].text[el] = currentChar;
                el++;
                ADV();
            }
            list->kicau[id].text[el] = '\0';
            printf("Kicauan telah diubah!\nDetil kicauan:");
            DisplayKicau(list->kicau[id]);
        }
    }
}