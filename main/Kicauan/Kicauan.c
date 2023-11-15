#include <stdio.h>
#include "Kicauan.h"
#include "time.h"
#include "../../modules/wordmachine/charmachine.h"
#include "../../modules/wordmachine/wordmachine.h"
#include "../../modules/time/datetime.h"
#include "../../modules/time/time.h"

void CreateKicau (Kicau *k, char author[])
{
    //increment ID
    static int cnt_id = 1;
    k->id = cnt_id++;

    //likes
    k->like = 0;

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

    k->author = stringToWord(author, 8);
    k->datetime = time(NULL);
    k->utasKicau = NULL;
}

void BaseDisplay (Kicau k)
{
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    DATETIME local;
    CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);

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
    TulisDATETIME(local);
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

void DisplayKicau (Kicau k)
{
    printf("\nSelamat! kicauan telah diterbitkan!\nDetil kicauan:");
    BaseDisplay(k);
}

void CreateKicauList(KicauList *list) {
    list->count = 0;
}

void AddKicauToList (Kicau k, KicauList *list)
{
    list->count = k.id;
    list->kicauan[list->count] = k;
}

void Kicauan (KicauList *list)
{
    for (int i = 1; i < list->count + 1; i++)
    {
        BaseDisplay(list->kicauan[i]);
    }
}

void SukaKicau (Account akunLogin, int id, KicauList *list, Kicau *k, AccountList* listakun, Graf teman)
{
    //Account ID user saat ini
    int id_user = GetAccountIdx(listakun, akunLogin);

    //Account ID username penulis kicauan yang ingin di-like
    int i = 0;
    boolean found = false;
    while (!found && i < list->count) {
        if (WordEqualAccount(*listakun->accounts[i].username, list->kicauan[k->id].author)) {
            found = true;
        }
        i++;
    }
    int id_penulis = i-1;

    if (!isIdInKicauan(id_penulis, list))
    {
        printf("Tidak ditemukan kicauan dengan ID = %d;", id);
    }
    else
    {
        //Jika dua akun tidak berteman
        if (!ELMTGRAF(teman, id_user, id_penulis))
        {
            if(WordEqual(*listakun->accounts[id_penulis].jenisAkun, publikkicau))
            {
                list->kicauan[k->id].like++;
                printf("Selamat! kicauan telah disukai!\nDetil kicauan:");
                BaseDisplay(list->kicauan[id]);
            }
            else
            {
                printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya");
            }
        } 
    }
}

boolean isIdInKicauan (int id, KicauList *list)
{
    if (id > list->count)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < list->count; i++)
        {
            if (list->kicauan[id].id == 0)
            {
                return false;
            }
        }
        return true;
    }
}

void UbahKicau (Account akunLogin, int id, KicauList *list)
{
    if (!isIdInKicauan(id, list))
    {
        printf("Tidak ditemukan kicauan dengan ID = %d!", id);
    }
    else
    {
        if (!WordEqual(list->kicauan[id].author, *akunLogin.username))
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
                list->kicauan[id].text[el] = currentChar;
                el++;
                ADV();
            }
            list->kicauan[id].text[el] = '\0';
            printf("Kicauan telah diubah!\nDetil kicauan:");
            DisplayKicau(list->kicauan[id]);
        }
    }
}
