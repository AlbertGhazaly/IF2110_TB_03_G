#include "DrafKicauan.h"

void buatdraf(Stack drafStack[], int userID, AccountList *list)
{
  drafkicau DrafUser;
  STARTSENTENCE();
  printf("Masukkan draf:\n");

  // Akuisisi dan simpan draf dalam stack
  STARTSENTENCE();
  CopyWordTo(&DrafUser.Draf, currentWord);
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);                 // Get the current time
  timeinfo = localtime(&rawtime); // Convert to local time

  // Access individual components
  int SS, M, HH, DD, MM, YY;
  getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
  DATETIME waktudraf;
  CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
  DrafUser.waktu = waktudraf;
  DrafUser.IDuser = userID;
  Push(&drafStack[userID], DrafUser);

  printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
  ADVSENTENCE();

  while (1)
  {
    STARTWORD();
    if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
    {
      // Pengguna ingin menghapus draf
      if (!IsEmptyStack(drafStack[userID]))
      {
        Pop(&drafStack[userID], &DrafUser);
        printf("Draf telah berhasil dihapus!\n");
      }
      else
      {
        printf("Tidak ada draf yang bisa dihapus.\n");
      }
      break;
    }
    else if (WordEqual(currentWord, stringToWord("SIMPAN", 6)))
    {
      // Pengguna ingin menyimpan draf
      printf("Draf telah berhasil disimpan!\n");
      break;
    }
    else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
    {
      // Pengguna ingin menerbitkan draf
      DATETIME waktuterbit;
      int SS, M, HH, DD, MM, YY;
      getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
      CreateDATETIME(&waktuterbit, DD, MM, YY, HH, M, SS);
      DrafUser.waktu = waktuterbit;
      Push(&drafStack[userID], DrafUser);
      ADVWORD();

      printf("Selamat! Draf kicauan telah diterbitkan!\n\n");
      // Tambahkan logikanya untuk menerbitkan draf
      printf("Detil kicauan:\n");
      printf("| ID = \n");
      printf("| ");
      printWord(*list->accounts[userID].username);
      printf("\n");
      printf("| ");
      TulisDATETIME(waktuterbit);
      printf("\n");
      printf("| ");
      printWord(DrafUser.Draf);
      printf("\n");
      printf("| ");
      printf("Disukai: 0\n");
      break;
    }
    else
    {
      printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'SIMPAN', 'TERBIT', atau 'KEMBALI'.\n");
    }
  }
}
void lihatdraf(Stack drafStack[], int userID, AccountList *list)
{
  drafkicau DrafUser;

  // Check if the user has any drafts
  if (!IsEmptyStack(drafStack[userID]))
  {
    printf("Ini draf terakhir anda:\n");
    printf("| ");
    TulisDATETIME(InfoTop(drafStack[userID]).waktu);
    printf("\n");
    printf("| ");
    printWord(InfoTop(drafStack[userID]).Draf);
    printf("\n");

    printf("\nApakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)\n");

    while (1)
    {
      STARTWORD();
      if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
      {
        // Pengguna ingin menghapus draf
        if (!IsEmptyStack(drafStack[userID]))
        {
          Pop(&drafStack[userID], &DrafUser);
          printf("Draf telah berhasil dihapus!\n");
        }
        else
        {
          printf("Tidak ada draf yang bisa dihapus.\n");
        }
        break;
      }
      else if (WordEqual(currentWord, stringToWord("UBAH", 4)))
      {
        // Pengguna ingin mengedit draf
        printf("Masukkan draf yang baru:\n");

        // Akuisisi dan simpan draf baru dalam stack
        STARTWORD();
        while (!EndWord)
        {
          CopyWordTo(&DrafUser.Draf, currentWord);
          ADVWORD();
        }

        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);                 // Get the current time
        timeinfo = localtime(&rawtime); // Convert to local time

        // Access individual components
        int SS, M, HH, DD, MM, YY;
        getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
        DATETIME waktudraf;
        CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
        DrafUser.waktu = waktudraf;
        Push(&drafStack[userID], DrafUser);

        printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");

        while (1)
        {
          STARTWORD();
          if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
          {
            // Pengguna ingin menghapus draf
            if (!IsEmptyStack(drafStack[userID]))
            {
              Pop(&drafStack[userID], &DrafUser);
              printf("Draf telah berhasil dihapus!\n");
            }
            else
            {
              printf("Tidak ada draf yang bisa dihapus.\n");
            }
            break;
          }
          else if (WordEqual(currentWord, stringToWord("SIMPAN", 6)))
          {
            // Pengguna ingin menyimpan draf
            printf("Draf telah berhasil disimpan!\n");
            break;
          }
          else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
          {
            // Di-pop karena draf telah diterbitkan
            Pop(&drafStack[userID], &DrafUser);
            // Pengguna ingin menerbitkan draf
            printf("Selamat! Draf kicauan telah diterbitkan!\n");
            // Tambahkan logikanya untuk menerbitkan draf
            break;
          }
          else if (WordEqual(currentWord, stringToWord("KEMBALI", 7)))
          {
            // Pengguna ingin kembali
            printf("Kembali ke draf sebelumnya.\n");
            break;
          }
          else
          {
            printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'SIMPAN', 'TERBIT', atau 'KEMBALI'.\n");
          }
        }
        break;
      }
      else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
      {
        // Pengguna ingin menerbitkan draf
        printf("Selamat! Draf kicauan telah diterbitkan!\n");
        // Tambahkan logikanya untuk menerbitkan draf
        break;
      }
      else if (WordEqual(currentWord, stringToWord("KEMBALI", 7)))
      {
        // Pengguna ingin kembali
        printf("Kembali ke draf sebelumnya.\n");
        break;
      }
      else
      {
        printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'UBAH', 'TERBIT', atau 'KEMBALI'.\n");
      }
    }
  }
  else
  {
    printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
  }
}
