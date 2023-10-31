#ifndef DRAFKICAUAN_H
#define DRAFKICAUAN_H

#include "../../modules/adt.h"

// Struct untuk menyimpan draf
struct Draft
{
  int id;
  char text[280]; // sesuai spek halaman 22
  char author[256];
  char datetime[30];
};

// Fungsi untuk menghitung jumlah baris dalam file
int HitungJumlahBaris(const char *namaFile);

// Fungsi untuk mengedit baris tertentu dari file
void editConfigFile(const char *filename, int line_number, const char *new_text);

// Fungsi untuk membuat draf baru
void BUAT_DRAF(const char *namaFile);

// Fungsi untuk melihat semua draf
void LIHAT_DRAF(const char *namaFile);

#endif
