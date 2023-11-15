#include "balasan.h"
#include "Pengguna/Pengguna.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern Word currentSentence;

void Createbalasan(Balasan *balasan, Account akunLogin) {
    static int nextID = 0; 
    balasan->id = ++nextID;
    // balasan->text = currentSentence;
    balasan->author = stringToWord(&akunLogin.username->TabWord, akunLogin.username->Length);
    balasan->datetime = getLocalTime();
    CreateTree(&(balasan->kumpulanBalasan));
}

void MembalasKicauan(Tree *balasanKicauan, Balasan *balasan, int balasanId) {
    addressTree tweetNode = getAddress(Root(*balasanKicauan), balasanId);
    if (tweetNode) {
        addressTree newbalasanNode = Alokasi(balasan->id);
        newbalasanNode->data = (int)balasan;
        AddChild(&tweetNode, newbalasanNode);
    } else {
        printf("Tweet with ID %d not found.\n", balasanId);
    }
}

void MembalasBalasan(Tree *balasanKicauan, Balasan *balasan, int parentId) {
    addressTree parentNode = getAddress(Root(*balasanKicauan), parentId);
    if (parentNode) {
        addressTree newbalasanNode = Alokasi(balasan->id);
        newbalasanNode->data = (int)balasan;
        AddChild(&parentNode, newbalasanNode);
    } else {
        printf("balasan with ID %d not found.\n", parentId);
    }
}

void DisplayBalasan(Tree balasanKicauan, int balasanId) {
    addressTree tweetNode = getAddress(Root(balasanKicauan), balasanId);
    if (tweetNode) {
        printTree(tweetNode, 0);
    } else {
        printf("Tweet with ID %d has no replies.\n", balasanId);
    }
}

void DeleteBalasan(Tree *balasanKicauan, int balasanId) {
    addressTree balasanNode = getAddress(Root(*balasanKicauan), balasanId);
    if (balasanNode) {
        CascadeDelete(balasanKicauan, balasanId);
    } else {
        printf("balasan with ID %d not found.\n", balasanId);
    }
}

void PrintBalasan(Balasan balasan) {
    struct tm *tm_struct = localtime(&balasan.datetime);
    DATETIME local;
    CreateDATETIME(&local, tm_struct->tm_mday, tm_struct->tm_mon + 1, tm_struct->tm_year + 1900, tm_struct->tm_hour, tm_struct->tm_min, tm_struct->tm_sec);

    printf("| ID = %d\n", balasan.id);
    printf("| ");
    printWord(balasan.author);
    printf("\n| ");
    TulisDATETIME(local);
    printf("\n| ");
    // printWord(balasan.text);
    printf("\n");
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
