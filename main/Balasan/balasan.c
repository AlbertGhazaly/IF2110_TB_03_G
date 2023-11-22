#include "balasan.h"
#include "Pengguna/Pengguna.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CreateBalasan(Balasan *balasan, Account akunLogin) {
    static int nextID = 0; 
    balasan->id = ++nextID;

    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    DATETIME local;
    CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);

    //baca text balasan
    int el = 0;
    printf("Masukkan balasan:\n");
    START();

    while (el < MAXChar)
    {
        if (currentChar == ';')
        {
            break;
        }
        balasan->text[el] = currentChar;
        el++;
        ADV();
    }

    balasan->text[el] = '\0';
    balasan->author = stringToWord(&akunLogin.username->TabWord, akunLogin.username->Length);
    balasan->datetime = local;
    CreateTree(&(balasan->kumpulanBalasan));
    printf("Selamat! Balasan telah diterbitkan!\n Detil balasan:\n");
    BaseDisplayBalasan(*balasan);
}

void BaseDisplayBalasan (Balasan b)
{
    printf("\n| ID = %d\n", b.id);

    //print author (without length seperti di ADT)
    printf("| ");
    int i;
    for (i = 0; i < b.author.Length; i++) 
    {
        printf("%c", b.author.TabWord[i]);
    }
    printf("\n");

    //print time upload kicauan
    printf("| ");
    TulisDATETIME(b.datetime);
    printf("\n");

    //print text
    int j = 0;
    printf("| ");
    while (b.text[j] != '\0')
    {
        printf("%c", b.text[j]);
        j++;
    }
}

void MembalasKicauan(Tree *balasanKicauan, Balasan *balasan, int balasanId) {
    addressTree kicauNode = getAddress(Root(*balasanKicauan), balasanId);
    if (kicauNode) {
        addressTree newbalasanNode = Alokasi(balasan->id);
        newbalasanNode->data = (int)balasan;
        AddChild(&kicauNode, newbalasanNode);
    } else {
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
    }
}

void MembalasBalasan(Tree *balasanKicauan, Balasan *balasan, int parentId) {
    addressTree parentNode = getAddress(Root(*balasanKicauan), parentId);
    if (parentNode) {
        addressTree newbalasanNode = Alokasi(balasan->id);
        newbalasanNode->data = (int)balasan;
        AddChild(&parentNode, newbalasanNode);
    } else {
        printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
    }
}

void DisplayBalasan(Tree balasanKicauan, int balasanId) {
    addressTree kicauNode = getAddress(Root(balasanKicauan), balasanId);
    if (kicauNode) {
        printTree(kicauNode, 0);
    } else {
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk balas kicauan tersebut!\n", balasanId);
    }
}

void DeleteBalasan(Tree *balasanKicauan, int balasanId) {
    addressTree balasanNode = getAddress(Root(*balasanKicauan), balasanId);
    if (balasanNode) {
        CascadeDelete(balasanKicauan, balasanId);
    } else {
        printf("Wah, tidak terdapat balasan yang ingin Anda hapus!\n");
    }
}

void CascadeDelete(Tree *balasanKicauan, int parentId) {
    addressTree parentNode = getAddress(Root(*balasanKicauan), parentId);
    if (parentNode) {
        addressTree child = FirstChild(parentNode);
        while (child) {
            CascadeDelete(balasanKicauan, Data(child));
            addressTree temp = child;
            child = NextSibling(child);
            Dealokasi(temp);
        }
        addressTree parent = getParent(Root(*balasanKicauan), parentNode);
        if (parent) {
            if (FirstChild(parent) == parentNode) {
                FirstChild(parent) = NextSibling(parentNode);
            } else {
                addressTree sibling = FirstChild(parent);
                while (NextSibling(sibling) != parentNode) {
                    sibling = NextSibling(sibling);
                }
                NextSibling(sibling) = NextSibling(parentNode);
            }
        } else {
            *balasanKicauan = (Tree){NULL};
        }
        Dealokasi(parentNode);
    }
}
