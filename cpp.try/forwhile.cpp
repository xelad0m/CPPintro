#include "pch.h"                    

#include<iostream>                  
using namespace std;                

int main() 
{
    // int S = 0;
    // int n = 1;
    // while (S < 100 && n != 0) {          // пока сумма не превысит 100
    //     cout << "Enter integer number:\n";
    //     cin >> n;
    //     S += n;
    // }
    // cout << S << endl;

    // double S = 0;                        // сумма геомет.прогрессии
    // for (int n = 1; n <= 1000; ++n) S += 1.0 / n;   // 1.0 приводит к вещественному
    // cout << S << endl;

    // double f, k, b;                      // итерирование функции k*x + b
    // cout << "Enter k, b: ";
    // cin >> k >> b;
    // for (double x = 0; x <= 1; x += 0.1){
    //     f = k * x + b;
    //     cout << f << endl;
    // }
    
    // double x = 0;                        // итерирование функции k*x + b
    // for (; x <= 1;)    {
    //     f = k * x + b;
    //     cout << f << endl;
    //     x += 0.1;
    // }

    // double x = 0;
    // for (;;){                            // итерирование функции k*x + b
    //     if (x > 1) break;
    //     f = k * x + b;
    //     cout << f << endl;
    //     x += 0.1;
    // }

    // const int secret_code = 13;             // do while
    // int code_ent;
    // do {
    //     cout << "Enter secret code: ";
    //     cin >> code_ent;
    // } while (code_ent != secret_code);

    float x, S = 0;
    int n = 0;
    do {                                    // continue
        cout << "Enter x: ";
        cin >> x;
        if (x < 0) continue;                // переход в начало цикла
        n++;
        S += x;
        cout << "Current sum: " << S << endl;
    } while (n < 5);
}