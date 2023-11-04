#include "kicauan.h"

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