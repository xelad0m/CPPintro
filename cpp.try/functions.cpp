#include "pch.h"                    

#include <iostream>    
using namespace std;                

void show_ar(int a[], int N);               // прототип должен быть объявлен до вызова
void modul(short x); 

float perimetr (float a, float b) {         // можно определять и сразу
    float res = 2 * (a + b);
    return res;     // float res = низзя
}


int main() 
{   
    int w = 5;
    float h = 3.4;

    float P1 = perimetr(w, h);
    float P2 = perimetr(5, 4);
    cout << P1 << " " << P2 << endl;

    int b[] = {4,3,5,-1,45,56,4,2};
    int N = sizeof(b)/sizeof(int);
    show_ar(b, N);

    modul(-3);

    return 0;
}

void show_ar(int a[], int N) {             // определение можно потом
    for (int i = 0; i < N; ++i)
        cout << a[i] << " ";
    cout << endl;
}

void modul(int x) {
    if (x < 0) x = -x;
    cout << x << endl;
}