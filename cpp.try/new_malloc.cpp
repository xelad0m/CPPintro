#include <iostream>   
using namespace std;                

// выделение памяти

int main() 
{   
    // short *ptr = 10000;      // нельзя, т.к. ОС не выделяла эту область памяти программе
    // *ptr = 0;    

    // оператор new (появился в С++), не только выделяет память, но и вызывает конструктор объекта
    // new <type> 
    // new <type>[<num>]

    // фукнция malloc (из С), просто выделяет память
    // void* malloc(<num_of_bytes>);

    int *p = new int;
    int *p2 = (int *)malloc(sizeof(int));       // malloc возвращает указатель void, а нужен int

    *p = 1;
    *p2 = 2;

    cout << *p << " " << *p2 << endl;
    
    // память нужно освобождать
    delete p;   // для new (delete[] p; если массив)
    free(p2);   // для malloc

    int n = 4;
    int *p3 = new int[n];   // при создании массива в памяти можно использовать для размера переменную (динамический массив)
    
    for (int i = 0; i < n; i++) {
        p3[i] = i + 1;
        cout << p3[i] << " ";
    };
    cout << endl;

    delete[] p3;

    return 0;
}