/*file driver.c*/
#include "DrafKicauan.h"
#include "DrafKicauan.c"

int main()
{
  Word kata;
  boolean sama;

  printf("BUAT_DRAF atau LIHAT_DRAF? ");
  STARTWORD();

  // Memasukkan kata yang diakuisisi ke dalam variabel 'kata'
  CopyWordTo(&kata, currentWord);

  // Membandingkan kata dengan kata referensi
  sama = WordEqual(kata, stringToWord("BUAT_DRAF", 9));
  // input harus diakhiri titik koma ";"

  while (getchar() != '\n');

  if (sama)
  {
    BUAT_DRAF("../../cfg/draf.config");
  }
  else
  {
    LIHAT_DRAF("draf.config");
  }

  return 0;
}
