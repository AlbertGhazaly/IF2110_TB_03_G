/*file driver.c*/
#include "DrafKicauan.h"
#include "DrafKicauan.c"

int main()
{
  Word kata;
  boolean isBuatDraf, isLihatDraf;

  printf("BUAT_DRAF atau LIHAT_DRAF? ");
  STARTWORD();

  // Memasukkan kata yang diakuisisi ke dalam variabel 'kata'
  CopyWordTo(&kata, currentWord);

  // Membandingkan kata dengan kata referensi
  isBuatDraf = WordEqual(kata, stringToWord("BUAT_DRAF", 9));
  isLihatDraf = WordEqual(kata, stringToWord("LIHAT_DRAF", 10));
  // input harus diakhiri titik koma ";"

  while (getchar() != '\n')
    ;

  if (isBuatDraf)
  {
    BUAT_DRAF("../../cfg/draf.config");
  }
  else if (isLihatDraf)
  {
    LIHAT_DRAF("../../cfg/draf.config");
  }
  else
  {
    printf("ulangi masukan");
  }

  return 0;
}
