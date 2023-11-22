#ifndef BALASAN_H
#define BALASAN_H

#include "../boolean.h"
#include "../../modules/adt.h"
#include "../../modules/tree/tree.h"
#include <time.h>

#define MAXChar 280
typedef struct kicau {
    int id;
    char text[MAXChar];
    Word author;
    DATETIME datetime;
    Tree kumpulanBalasan;  
 } Balasan;

void CreateBalasan(Balasan *balasan, Account author);
void BaseDisplayBalasan (Balasan b);
void MembalasKicauan(Tree *balasanKicauan, Balasan *balasan, int balasanId);
void MembalasBalasan(Tree *balasanKicauan, Balasan *balasan, int parentId);
void DisplayBalasan(Tree balasanKicauan, int balasanId);
void DeleteBalasan(Tree *balasanKicauan, int balasanId);
void CascadeDelete(Tree *balasanKicauan, int parentId);

#endif