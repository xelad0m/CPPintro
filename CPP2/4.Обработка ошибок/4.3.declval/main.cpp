#include <iostream>
#include <utility> // std::declval

// внутри do_math объекты типа T
// - копируются
// - присваиваются
// - складываются оператором +
template<class T>
void do_math() 
    noexcept(noexcept(std::declval<T&>() + std::declval<T&>()) 
             && std::is_nothrow_copy_constructible<T>::value
             && std::is_nothrow_assignable<T&, T>::value)
{}


int main()
{
    bool b1 = noexcept(do_math<int>()); // true
    bool b2 = noexcept(do_math<std::string>()); // false

    std::cout << b1 << "\n";
    std::cout << b2 << "\n";

    return 0;
}