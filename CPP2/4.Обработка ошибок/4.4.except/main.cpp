#include <iostream>
#include <utility> // std::pair

struct A 
{
    A() { std::cout << "A\n"; };
};

struct B
{
    B() { std::cout << "B\n"; };
};

template<class T, class V>
std::pair<T*,V*> fun() 
{ return std::make_pair(new T, new V); }

int main()
{
    fun<A,B>();

    return 0;
}