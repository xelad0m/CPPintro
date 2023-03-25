#include <iostream>

struct Unit {};
struct Elf: virtual Unit {};
struct Archer: virtual Unit {};
struct ElfArcher: Elf, Archer {};

int main() {
    ElfArcher* elfArcher = new ElfArcher();
    Elf* elf = static_cast<Elf*>(elfArcher);
    Archer* archer = dynamic_cast<Archer*>(elfArcher);

    std::cout << "ElfArcher*: " << elfArcher << std::endl;
    std::cout << "-> cast to Elf*   : " << elf << std::endl;
    std::cout << "-> cast to Archer*: " << archer << std::endl << std::endl;

    elfArcher = static_cast<ElfArcher*>(elf);
    std::cout << "ElfArcher* from Elf*: " << elfArcher << std::endl;
      
    elfArcher = static_cast<ElfArcher*>(archer);
    std::cout << "ElfArcher* from Archer*: " << elfArcher << std::endl;

    elfArcher = (ElfArcher*)archer;
    std::cout << "(ElfArcher*)archer: " << elfArcher << std::endl;
    ElfArcher* elfArcher1 = (ElfArcher*)(void*)archer;
    std::cout << "(ElfArcher*)(void *)archer: " << elfArcher1 << std::endl;

    return 0;
}
