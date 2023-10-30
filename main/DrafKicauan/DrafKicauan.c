#include "DrafKicauan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// SPEK https://docs.google.com/document/d/1yy0SLsXEE0e-ZBxMSrd0Gz9AOSWqJw1trtTqDjeyfsk/edit

// Struct untuk menyimpan draf
struct Draft
{
  int id;
  char text[280]; // sesuai spek halaman 22
  char author[256];
  char datetime[256];
};

// Fungsi untuk menghitung jumlah baris dalam file
int HitungJumlahBaris(const char *namaFile)
{
  FILE *file = fopen(namaFile, "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return -1; // Mengembalikan nilai negatif untuk menandakan kesalahan
  }

  int jumlahBaris = 0;
  char karakter;

  while ((karakter = fgetc(file)) != EOF)
  {
    if (karakter == '\n')
    {
      jumlahBaris++;
    }
  }

  fclose(file);
  return jumlahBaris;
}

// Fungsi untuk mengedit baris tertentu dari file
void editConfigFile(const char *filename, int line_number, const char *new_text)
{
  FILE *file = fopen(filename, "r+");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }

  // Loop untuk mencapai baris yang ingin diubah
  int current_line = 0;
  char buffer[1024];
  while (current_line < line_number)
  {
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
      printf("Baris yang ingin diubah tidak ditemukan.\n");
      fclose(file);
      return;
    }
    current_line++;
  }

  // Kembali ke awal baris yang ingin diubah
  fseek(file, -ftell(file), SEEK_CUR);

  // Tulis teks baru ke dalam file
  fprintf(file, "%s", new_text);

  fclose(file);
  printf("Perubahan telah disimpan.\n");
}

// Fungsi untuk membuat draf baru
void BUAT_DRAF(const char *namaFile)
{
  FILE *file = fopen(namaFile, "a");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }

  int jumlahBaris = HitungJumlahBaris(namaFile);
  // Tambahkan 1 untuk mewakili draf baru
  jumlahBaris++;

  if (jumlahBaris == 1)
  {
    fprintf(file, "1\n");
  }

  // Kembali ke awal file
  rewind(file);

  // Kembali ke akhir file untuk menambahkan draf baru
  fseek(file, 0, SEEK_END);

  struct Draft newDraft;
  printf("Masukkan teks draf: ");
  fgets(newDraft.text, sizeof(newDraft.text), stdin);

  printf("Masukkan penulis: ");
  fgets(newDraft.author, sizeof(newDraft.author), stdin);

  printf("Masukkan tanggal dan waktu (contoh: 14/10/2023 11:09:18): ");
  fgets(newDraft.datetime, sizeof(newDraft.datetime), stdin);

  newDraft.id = jumlahBaris / 4 + 1; // ID adalah jumlah baris dibagi 4

  // Tulis draf ke file draft.config dengan pemisah newline
  fprintf(file, "%d\n", newDraft.id);
  fprintf(file, "%s", newDraft.text);
  fprintf(file, "%s", newDraft.author);
  fprintf(file, "%s", newDraft.datetime);

  fclose(file);

  const char filename[] = "draft.config";
  int line_number = 1;
  char new_text[20]; // Sesuaikan ukuran buffer sesuai kebutuhan
  snprintf(new_text, sizeof(new_text), "%d", newDraft.id);
  editConfigFile(filename, line_number, new_text);

  printf("Draf baru telah ditambahkan ke draft.config.\n");
}

// Fungsi untuk melihat semua draf
void LIHAT_DRAF(const char *namaFile)
{
  FILE *file = fopen(namaFile, "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return;
  }

  printf("Daftar Draf:\n");

  struct Draft draft;
  int id;
  while (fscanf(file, "%d # draf dengan ID ke-%d", &id, &id) == 2)
  {
    printf("ID: %d\n", id);
    fgets(draft.text, sizeof(draft.text), file);
    fgets(draft.author, sizeof(draft.author), file);
    fgets(draft.datetime, sizeof(draft.datetime), file);
    printf("Teks: %s", draft.text);
    printf("Penulis: %s", draft.author);
    printf("Tanggal dan Waktu: %s", draft.datetime);
    printf("\n");
  }

  fclose(file);
}

int main()
{
  // Contoh penggunaan fungsi BUAT_DRAF dan LIHAT_DRAF

  char pilihan[20];
  scanf("%s", pilihan);
  getchar(); // Membersihkan karakter newline

  if (strcmp(pilihan, "BUAT_DRAF") == 0)
  {
    BUAT_DRAF("draft.config");
  }
  else if (strcmp(pilihan, "LIHAT_DRAFT") == 0)
  {
    LIHAT_DRAF("draft.config");
  }

  return 0;
}
