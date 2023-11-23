#include "balasan.h"
#include "../includeADT.h"
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
    BaseDisplayTree(*balasan);
}

void BaseDisplayTree (Balasan b)
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

void CreateTree(Tree *T){
    (*T).root = NULL;
}

addressTree Alokasi(int X){
    addressTree P = (addressTree) malloc(sizeof(Node));
    if(P != NULL){
        Data(P) = X;
        FirstChild(P) = NULL;
        NextSibling(P) = NULL;
    }
    return P;
}

void Dealokasi(addressTree P){
    free(P);
}

void AddChild(addressTree *P, addressTree C){
    if(*P == NULL){
        *P = C;
    }else{
        addressTree Q = *P;
        while(FirstChild(Q) != NULL){
            Q = FirstChild(Q);
        }
        FirstChild(Q) = C;
    }
}

void AddSibling(addressTree *P, addressTree S){
    if(*P == NULL){
        *P = S;
    }else{
        addressTree Q = *P;
        while(NextSibling(Q) != NULL){
            Q = NextSibling(Q);
        }
        NextSibling(Q) = S;
    }
}

void printSiblings(addressTree P){
    if(P != NULL){
        printf("%d ", Data(P));
        printSiblings(NextSibling(P));
    }
}

void printChild(addressTree P){
    if(P != NULL){
        printf("%d ", Data(P));
        printChild(FirstChild(P));
        printSiblings(NextSibling(P));
    }
}

void printTree (addressTree P, int h){
    if(P != NULL){
        int i;
        for(i = 0; i < h; i++){
            printf("    ");
        }
        printf("%d\n", Data(P));
        printTree(FirstChild(P), h+1);
        printTree(NextSibling(P), h);
    }
}

addressTree getAddress (addressTree P, int X){
    if(P != NULL){
        if(Data(P) == X){
            return P;
        }else{
            addressTree Q = getAddress(FirstChild(P), X);
            if(Q != NULL){
                return Q;
            }else{
                return getAddress(NextSibling(P), X);
            }
        }
    }else{
        return NULL;
    }
}

addressTree getParent(addressTree root,addressTree C){
    // I.S. C terdefinisi
    // F.S. mengembalikan addressTree parent dari C
    if(FirstChild(root) == C){
        return root;
    }else{
        addressTree Q = FirstChild(root);
        while(Q != NULL){
            if(NextSibling(Q) == C){
                return root;
            }else{
                addressTree R = getParent(Q, C);
                if(R != NULL){
                    return R;
                }else{
                    Q = NextSibling(Q);
                }
            }
        }
        return NULL;
    }
}