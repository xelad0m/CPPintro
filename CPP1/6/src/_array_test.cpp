#include <iostream>
#include <string>

#include "array.hpp"

void self_test()
{
    std::cout << "placement new copy test:" << std::endl;

    typedef Array<int> Arr;
    
    int size = 10;

    Arr a(size, 42);            // К. с параметрами
    for (int i=0; i<size; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    Arr b = a;                 // К. копирования
    for (int i=0; i<size; ++i)
        std::cout << b[i] << " ";
    std::cout <<std::endl;
    
    Arr c;
    c = b;                      // оп. присваивания
    c = c;
    for (int i=0; i<size; ++i)
        std::cout << c[i] << " ";
    std::cout <<std::endl;

    std::cout << "flatten test:" << std::endl;
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout);           // выводит на экран строку "10 20"

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout);  // выводит на экран строку "10 20\n10 20\n\n"

    Array<double> doubles(10, 42.0);
    Array< Array<double> > dd(10, doubles);
    flatten(dd, std::cout);             // работать должно не только для типа int

    std::cout << "min/max test:" << std::endl;
    Array<int> iis(3);
    iis[0] = 10;
    iis[1] = 2;
    iis[2] = 15;
    int min = minimum(iis, Less<int>());    // 2
    int max = minimum(iis, Greater<int>()); // 15

    std::cout << min << " " << max << std::endl;

}

int main()
{
    self_test();
    return 0;
}