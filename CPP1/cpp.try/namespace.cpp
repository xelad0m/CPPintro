#include <iostream>    
using namespace std;                

double sum_ar(double a[], int N) {
    double S = 0;
    for (int i = 0; i < N; ++i)
        S += a[i];
    return S;
}

void iter() {
    int var = 1;
    static int var_st = 1;  // если существует, то не пересоздается при вызове
    cout << "var=" << var++ << " var_st=" << var_st++ << endl;
}


int main() 
{   
    int t = 1;
    {
        int t = 2;
        {
            int t = 3;
            cout << t << endl;
        }
        cout << t << endl;
    }
    cout << t << endl;


    double ar[] = {2, 5, -3, 0, 1, 7};
    int L = sizeof(ar)/sizeof(double);

    for (int i = 0; i < L; ++i)
        cout << ar[i] << " ";
    cout << endl;

    cout << sum_ar(ar, L) << endl;          // локальные переменные


    extern short y;                         // внешняя область видимости
    cout << y << endl;

    for (int i = 0; i < 4; ++i) iter();     // статические переменные - видны только в своей области видимости, но сохраняются между вызовами

    const int var_const = 10;               // константы
    // var_conts = 5;                       // exception

    return 0;
}

short y = 10;