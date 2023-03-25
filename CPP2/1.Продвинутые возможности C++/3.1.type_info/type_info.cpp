#include <typeinfo>
#include <iostream>

struct Unit {
    virtual ~Unit() {};
};

struct Elf : Unit { };

int main() {
    int a = 27;
    int const b = 412;
    float d = 0.5;
    int * pa = &a;

    std::cout << typeid(a).name() << "\n";      // i
    std::cout << typeid(b).name() << "\n";      // i
    std::cout << typeid(d).name() << "\n";      // f
    std::cout << typeid(pa).name() << "\n";     // Pi

    Elf e;
    Unit & ur = e;
    Unit * up = &e;
                                                        // virt     NO virt
    std::cout << typeid(ur).name() << "\n";             // 3Elf     4Unit
    std::cout << typeid(*up).name() << "\n";            // 3Elf     4Unit
    std::cout << typeid(up).name() << "\n";             // P4Unit   P4Unit
    std::cout << typeid(Elf).name() << "\n";            // 3Elf     3Elf
    std::cout << (typeid(ur) == typeid(Elf)) << "\n";   // 1        0




    return 0;
}