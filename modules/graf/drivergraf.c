#include <stdio.h>
#include "graf.h"

int main() {
    Graf g;
    ListGraf l;

    // Membuat graf kosong
    createEmptyGraf(&g);

    // Menampilkan graf kosong
    printf("Graf Awal (kosong):\n");
    displayGraf(g, ROW_GRAF);

    // Membuat list graf kosong
    CreateListGraf(&l);

    // Menampilkan list graf kosong
    printf("\nListGraf Awal (kosong):\n");
    for (int i = 0; i < CAPACITYGRAF; i++) {
        printf("%d ", ELMTLISTGRAF(l, i));
    }
    printf("\n");

    // Menambahkan satu edge pada graf
    ELMTGRAF(g, 0, 1) = 1;

    // Menampilkan graf setelah penambahan edge
    printf("\nGraf setelah penambahan edge:\n");
    displayGraf(g, ROW_GRAF);

    // Mendapatkan node yang terhubung dengan node 0
    getOne(g, 0, &l);

    // Menampilkan list graf setelah mendapatkan node terhubung
    printf("\nListGraf setelah mendapatkan node terhubung dengan node 0:\n");
    for (int i = 0; i < CAPACITYGRAF; i++) {
        printf("%d ", ELMTLISTGRAF(l, i));
    }
    printf("\n");

    return 0;
}
