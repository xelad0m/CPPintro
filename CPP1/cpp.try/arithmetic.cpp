#include <iostream>


using namespace std;                // std::cout

int main() 
{
    setlocale(LC_ALL, "rus");       // необязательно

    // float a = 8.6;
    // double b = 3 * a;
    // int c = (int)(3 * a);           // приведение типа
    // cout << b << " " << c << endl;

    // int d = 7;
    // int e = 2;
    // double f = d / (double)e;       // без приведения одного из аргументов останется int
    // cout << f << endl;

    // short var = 0;
    // var++;                          // var = var + 1
    // cout << var;

    int a, b, c = 10, d = 10;
    a = c++;    // a=10     сначала присвоить, потом инкремент
    b = ++d;    // b=11     сначала инкремент, потом присвоить
    cout << a << " " << b << " " << c << " " << d << " " << endl;

    a += 5;                             // тоже работает со всеми арифм.операциями

    return 0;
}