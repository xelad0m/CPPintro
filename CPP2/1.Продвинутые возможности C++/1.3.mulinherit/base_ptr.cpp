/*
Напишите функцию D1BaseToD2Base, которая преобразует 
указатель типа Base на объект типа D3, который ссылается 
на экземпляр Base, соответствующий D1, в указатель, 
ссылающийся на экземпляр Base соответствующий D2.
*/

#include <iostream>


struct Base { int i; };	// 4 байта разницы

struct D1 : Base {  };

struct D2 : Base {  }; 

struct D3 : D1, D2 {  };

Base const * D1BaseToD2Base( Base const * base )
{
    return (Base const *)(D2 *)(D3 *)(D1 *)base;

    // как вариант: будет неявно преобразован к Base const * 
    // return (D2*)(D3*)(D1*) base;

    // как вариант: без C-style cast
    // return static_cast<Base const*>(static_cast<D2 const*>(static_cast<D3 const*>(static_cast<D1 const*>(base))));

    // по смыслу классы должны быть полиморфными
    // поэтому самый корректный вариант будет 
    // return dynamic_cast<Base const *> (dynamic_cast<D2 const *> (dynamic_cast<D3 const *> (base)));
}

int main() {
    D3 * d3 = new D3();
    D1 * d1 = d3;
    Base * b1 = d1;

//    std::cout << "&d3:" << d3 << std::endl;
//    std::cout << "&d1:" << d1 << std::endl;
    std::cout << "D3:D1:Base:" << b1 << std::endl;
    std::cout << "D3:D2:Base:" << D1BaseToD2Base(b1) << std::endl;


    return 0;
}
