#ifndef SimpanMuat_H
#define SimpanMuat_H
#include "../includeADT.h"
#define MAXChar 280
char* concatStr(char path[],char folder[]);
boolean isDirExist(char path[]);
void loadUtas(char filename[],KicauList* kList, int* jumlahUtas, AccountList akunList);
void loadTweetCnfg(char filename[],KicauList* kList);
void ReadUser_FILE(char filename[], AccountList *list, Graf *teman, prioqueuefren * Q);
void ReadDraf_FILE(char filename[], AccountList *list, Stack *S);
/*Membaca file Draf dari Draf.config kedalam program
    I.S. Stack terdefinisi dan AccountList sudah diakuisisi dari user.config
    F.S. Stack terisi dengan drafkicauan dari Draf.Config
    */


void SaveUser_FILE(char filename[], AccountList *list, Graf Teman, prioqueuefren Q);
void saveUtas(char filename[],KicauList* kList, int jumlahUtas, AccountList akunList);
void saveTweet(char filename[],KicauList kList);

#endif