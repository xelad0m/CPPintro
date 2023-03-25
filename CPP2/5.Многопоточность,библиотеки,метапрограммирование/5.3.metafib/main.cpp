#include <iostream>

// Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи
template<int N>
struct Fib
{
    static int const value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0>
{
    static int const value = 0;
};

template<>
struct Fib<1>
{
    static int const value = 1;
};


int main()
{
    std::cout << Fib<10>::value << std::endl;     // 55

    return 0;
}