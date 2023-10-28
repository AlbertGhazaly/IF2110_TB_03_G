#include <stdio.h>
#include "includeADT.h"

// 1 - WordEqual
boolean WordEqual(Word a, Word b) {
    if (a.Length != b.Length) {
        return false;
    } else {
        int n = a.Length;

        boolean equal = true;
        int i = 0;
        while (equal && (i < n)) {
            if ((a.TabWord[i] != b.TabWord[i])) {
                equal = false;
            } else {
                i += 1;
            }
        }

        return equal;
    }
}



void signUp(){
    
}