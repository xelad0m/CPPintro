#include <iostream>
#include "namespace.hpp"

int main(void) {
    MyLib::MyClass c;
    MyLib::MyClassPtr p(new MyLib::MyClass ());

    std::cout << c.data << "\n" << (*p).data << "\n";
    
    std::cout << p << "\n" << p.get() << "\n";

    return 0;
}