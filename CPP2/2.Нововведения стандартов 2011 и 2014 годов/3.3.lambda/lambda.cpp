#include <iostream>
#include <functional>   // std::function

// пример 1
template<class F>
void for_each_int(int * p, int * q, F f)
{
    for ( ; p != q; ++p )
        f(*p);
}

// возводит переданное число в квадрат
auto square_fun = [](int & i) { i *= i; };
// std::function<void (int &)> square_fun = [](int & i) { i *= i; };    // C++03


// пример 2 поиск с внешним компаратором
template<class F>
int * find_if(int * p, int * q, F f)
{
    for ( ; p != q; ++p ) {
        if (f(*p))
            return p;
    }
    return q;
}

// принимает массив значений типа int через два указателя и возвращает безымянную 
// функцию, которая в свою очередь принимает значение типа int и проверяет, есть ли
// это значение в переданном массиве
auto gen_finder = [](int * pr1, int * pr2) { 
    return [pr1, pr2](int x) -> bool { 
        for (int * curr = pr1; curr != pr2; ++curr)
            if (*curr == x)
                return true;
        return false; 
    }; 
};

int main() {
    int i = 10;
    int * p = &i;
    square_fun(*p);
    std::cout << i << "\n";

    int m[10] = {1,2,3,4,5,6,7,8,9,10};

    for_each_int(m, m + 10, square_fun);

    for (int x : m) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    int primes[5] = {2,3,5,7,11};
    int arr[10] = {0,0,1,1,4,6,7,8,9,10};

    // first_prime будет указывать на число 7
    int * first_prime = find_if(arr, arr + 10, gen_finder(primes, primes + 5));
    std::cout << "first_prime=" << *first_prime << "\n";

    return 0;
}