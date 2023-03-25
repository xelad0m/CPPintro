#include <iostream>

int foo(int i) { return 1; }

namespace ru
{
    int foo(float f)  { return 2; }

    int foo(double a, double b) { return 3; }

    namespace spb {
        int global = foo(5);    // 2
    }
}


int main(void) {
    
    std::cout << ru::spb::global << "\n";

    return 0;
}