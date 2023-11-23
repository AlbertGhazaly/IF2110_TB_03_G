#include "utas.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>




boolean lanjut(Word input){
    Word ya = {"YA",2};
    Word tidak = {"TIDAK",5};
    if (WordEqual(input,ya)){
        return true;
    }else if (WordEqual(input, tidak)){
        return false;
    }else{
        STARTWORD();
        lanjut(currentWord);
    }
}
void copyWordToString(char* destination,Word input){
    destination = "";
    int i;
    for (i=0;i<input.Length;i++){
        (destination[i]) = input.TabWord[i];
    }
    (destination[i]) = '\0';
}