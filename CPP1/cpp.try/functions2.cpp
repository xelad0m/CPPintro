#include <iostream>    
using namespace std;                

int modul(int x) {                            // т.к. целые быстрее, то полезно иметь для них свою реализацию, а не авто-приводить тип
    if (x < 0) x = -x;
    return x;
}

double modul(double x) {                      // перегрузка функций (компилятор определяет по типу аргумента)
    if (x < 0) x = -x;
    return x;
}

void show_args(short a = 10, float b = 20, int c = 30) {    // default args values
    cout << a << " "  << b << " "  << c << endl;

}

void up_n_down(int n) {                         // рекурсия
    cout << "Level down " << n << endl;
    if (n < 4) up_n_down(n + 1);
    cout << "Level up " << n << endl;
}

int main() 
{   
    int a1 = modul(-3);
    int a2 = modul(-3.5);
    double a3 = modul(-3);
    double a4 = modul(-3.5);
    cout << a1 << " " << a2 << " " << a3 << " " << a4 << endl;

    show_args();                // по позиции
    show_args(1);
    show_args(1, 2);
    show_args(1, 2, 3);

    up_n_down(1);

    return 0;
}
