#include <stdio.h>
#include "stack.h"

void CreateEmpty(Stack *S)
{
    Top(*S) = Nil;
}

boolean IsEmpty(Stack S){
    return Top(S) == Nil;
}

boolean IsFull(Stack S){
    return Top(S) == MaxEl - 1;
}

void Push(Stack *S, drafkicau X){
    Top(*S)++;
    InfoTop(*S) = X;
}

void Pop(Stack *S, drafkicau * X){
    *X = InfoTop(*S);
    Top(*S)--;
}