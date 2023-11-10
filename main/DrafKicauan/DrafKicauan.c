#include "DrafKicauan.h"

Stack *createSTackDrafPerUser(Stack S)
{
  Stack *drafStack = (Stack *)malloc(20 * sizeof(Stack)); // Allocate memory for an array of 20 Stack

  for (int i = 0; i < 20; i++)
  {
    CreateEmptyStack(&drafStack[i]);
  }

  int i = 0;
  while (!IsEmptyStack(S))
  {
    drafkicau X;
    Pop(&S, &X);
    if (X.IDuser == i)
    {
      Push(&drafStack[i], X);
    }
    i++;
  }
  return drafStack; // Return a pointer to the array of Stack
}

// void buatdraf(Stack *draf, int userID, AccountList *list)
// {
//   Stack *drafStack = createSTackDrafPerUser(*draf);
//   drafkicau DrafUser;
//   printf("Masukkan draf:\n");

//   // Akuisisi dan simpan draf dalam stack
//   STARTWORD();
//   while (!EndWord)
//   {
//     CopyWordTo(&DrafUser.Draf, currentWord);
//     ADVWORD();
//   }

//   // TIME
//   time_t rawtime;
//   struct tm *timeinfo;
//   time(&rawtime);                 // Get the current time
//   timeinfo = localtime(&rawtime); // Convert to local time
//   // Access individual components
//   int SS, M, HH, DD, MM, YY;
//   getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
//   DATETIME waktudraf;
//   CreateDATETIME(&waktudraf, DD, MM, YY, HH, M, SS);
//   // TIME

//   DrafUser.waktu = waktudraf;
//   DrafUser.IDuser = userID;
//   Push(&drafStack[userID], DrafUser);

//   printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");

//   while (1)
//   {
//     STARTWORD();
//     if (WordEqual(currentWord, stringToWord("HAPUS", 5)))
//     {
//       // Pengguna ingin menghapus draf
//       if (!IsEmptyStack(drafStack[userID]))
//       {
//         Pop(&drafStack[userID], &DrafUser);
//         printf("Draf telah berhasil dihapus!\n");
//       }
//       else
//       {
//         printf("Fungsi BUAT_DRAF gagal memasukkan ke stack drafStack[userID]\n");
//       }
//       break;
//     }
//     else if (WordEqual(currentWord, stringToWord("SIMPAN", 6)))
//     {
//       // Pengguna ingin menyimpan draf
//       printf("Draf telah berhasil disimpan!\n");
//       break;
//     }
//     else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
//     {
//       // Pengguna ingin menerbitkan draf
//       DATETIME waktuterbit;
//       int SS, M, HH, DD, MM, YY;
//       getlocaltime(&SS, &M, &HH, &DD, &MM, &YY);
//       CreateDATETIME(&waktuterbit, DD, MM, YY, HH, M, SS);
//       DrafUser.waktu = waktuterbit;
//       DrafUser.IDuser = userID;
//       Push(&drafStack[userID], DrafUser);

//       printf("Selamat! Draf kicauan telah diterbitkan!\n\n");
//       // Tambahkan logikanya untuk menerbitkan draf
//       printf("Detil kicauan:\n");
//       printf("| ID = \n");
//       printf("| ");
//       printWord(*list->accounts[userID].username);
//       printf("\n");
//       printf("| ");
//       TulisDATETIME(waktuterbit);
//       printf("\n");
//       printf("| ");
//       printWord(DrafUser.Draf);
//       printf("\n");
//       printf("| ");
//       printf("Disukai: 0\n");
//       break;
//     }
//     else
//     {
//       printf("Perintah tidak valid. Silakan masukkan 'HAPUS', 'SIMPAN', 'TERBIT', atau 'KEMBALI'.\n");
//     }
//   }
//   // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
//   for (int i = 0; i < 20; i++)
//   {
//     while (!IsEmptyStack(drafStack[i]))
//     {
//       Pop(&drafStack[i], &DrafUser);
//       Push(draf, DrafUser);
//     }
//   }
// }

void lihatdraf(Stack *draf, int userID, AccountList *list)
{
  Stack *drafStack = createSTackDrafPerUser(*draf);

  drafkicau DrafUser;

  // Pengguna ingin melihat draf terakhir
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
          // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
          for (int i = 0; i < 20; i++)
          {
            while (!IsEmptyStack(drafStack[i]))
            {
              Pop(&drafStack[i], &DrafUser);
              Push(draf, DrafUser);
            }
          }
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
        DrafUser.IDuser = userID;
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
              // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
              for (int i = 0; i < 20; i++)
              {
                while (!IsEmptyStack(drafStack[i]))
                {
                  Pop(&drafStack[i], &DrafUser);
                  Push(draf, DrafUser);
                }
              }
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
            // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
            for (int i = 0; i < 20; i++)
            {
              while (!IsEmptyStack(drafStack[i]))
              {
                Pop(&drafStack[i], &DrafUser);
                Push(draf, DrafUser);
              }
            }
            printf("Draf telah berhasil disimpan!\n");
            break;
          }
          else if (WordEqual(currentWord, stringToWord("TERBIT", 6)))
          {
            // Di-pop karena draf telah diterbitkan
            Pop(&drafStack[userID], &DrafUser);
            // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
            for (int i = 0; i < 20; i++)
            {
              while (!IsEmptyStack(drafStack[i]))
              {
                Pop(&drafStack[i], &DrafUser);
                Push(draf, DrafUser);
              }
            }
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
        // push semua isi dari stackPerUser ke AllUserStack (yakni Stack draf)
        for (int i = 0; i < 20; i++)
        {
          while (!IsEmptyStack(drafStack[i]))
          {
            Pop(&drafStack[i], &DrafUser);
            Push(draf, DrafUser);
          }
        }
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
