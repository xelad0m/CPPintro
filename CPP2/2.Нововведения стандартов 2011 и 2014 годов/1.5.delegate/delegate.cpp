#include <iostream>

struct Base {
    Base(int value) : data(value) {};
protected:
    void f() { std::cout << "Base::f()\n"; }
    int data = 0;
};

struct Derived : public Base {
    using Base::Base;
    using Base::f;
    using Base::data;
};

int main() 
{   
    Derived d(42);

    d.f();
    std::cout << d.data << std::endl;

    return 0;   
}