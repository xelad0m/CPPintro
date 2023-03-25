#include <string>
#include <typeinfo>
#include <iostream>


int main()
{
    std::string s = "Compiler";

    auto sz = s.size();

    auto c1 = s[0];

    decltype(s[0]) c2 = s[7];

    decltype(s[0] + s[7]) c3 = s[1];

    decltype(s)   sa = s;

    decltype((s)) sb = s;

    c1 = 'K';
    c2 = '!';
    
    std::cout << typeid(s).name() << "\n";
    std::cout << typeid(sz).name() << "\n";
    std::cout << typeid(c1).name() << "\n";
    std::cout << typeid(c2).name() << "\n";
    std::cout << typeid(c3).name() << "\n";
    std::cout << s << "\n";

/*

NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
m
c
c
i

Для форматирования вывода typeid().name() в реализации g++ есть утилита c++filt

./decltype | c++filt -t
std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >
unsigned long
char
char
int

*/
    return 0;
}