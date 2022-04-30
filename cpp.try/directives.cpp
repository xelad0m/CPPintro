#include "pch.h"                    // " " - custom headers
#include<iostream>                  // < > - builtins

#define STDIO
#ifdef STDIO                        // проверка существования константы
    #include<stdio.h>                   // printf
#endif

#define TWO 2
//#undef TWO                        // отменяет define
#define FOUR TWO*TWO
#define PX cout << "X равно " << x << endl
#define STR "X равно "
#define SQUARE(X) X*X
#define P(A, B) 2*(A+B)             // периметр

using namespace std;                // std::cout

int main() 
{
    setlocale(LC_ALL, "rus");       // необязательно у меня

    int x = TWO;
    PX;
    x = FOUR;
    cout << STR << x << endl;
    x = SQUARE(3);
    PX;

    x = P(3, 5);
    PX;
    #ifdef STDIO
        printf("(printf) X равно %d\n", x);
    #endif

    return 0;
}