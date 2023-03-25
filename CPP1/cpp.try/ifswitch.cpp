#include "pch.h"                    

#include<iostream>                  
using namespace std;                

int main() 
{
    // int x;
    // cin >> x;                    // ввод с клавиатуры
    // if (x < 0) x = x * (-1);
    // cout << x << endl;           // модуль числа

    // setlocale(LC_ALL, "rus");
    // float x;
    
    // cout << "Введите число : ";
    // cin >> x;

    // if (x < 0) cout << "Введенное число " << x << " является отрицательным.\n";
    // else if (x > 0) cout << "Введенное число " << x << " является положительным.\n";
    // else cout << "Введенное число равно 0.\n";

    // double a;
    // cin >> a;

    // if (a >=-2 && a <= 5)   // AND
    //         cout << "a принадлежит [-2; 5]" << endl;

    // if (a < -2 || a > 5)    // OR
    //         cout << "a не принадлежит [-2; 5]" << endl;

    // if (!(a < -2 || a > 5)) // NOT
    //         cout << "a принадлежит [-2; 5]" << endl;


    short item;
    cout << "0 - exit\n1 - case 1\n2 - case 2\n3 - case 3\n";
    cin >> item;

    switch (item) {
        case 1: cout << "case1\n"; break;
        case 2: cout << "case2\n"; break;
        case 3: cout << "case3\n"; break;
        default: cout << "no selection\n3";
    }

    return 0;
}