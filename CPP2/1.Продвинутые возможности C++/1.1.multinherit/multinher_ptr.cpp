#include <iostream>

struct unitid {
    explicit unitid( int i = 0 ) : id(i) {}
    int id;
};

struct Unit {
    Unit(unitid id, int hp): id_(id), hp_(hp) {}
    virtual unitid id() const { return id_; }
    virtual int hp() const { return hp_; }
private:
    unitid id_;
    int    hp_;
};
struct Elf: Unit {
    explicit Elf(unitid id, int hp) : Unit(id, hp) {}
private:
    int dataElf;
};
struct Archer: Unit{
    explicit Archer(unitid id, int hp) : Unit(id, hp) {}
private:
    int dataArcher;
 };
struct ElfArcher: Elf, Archer {
    ElfArcher(unitid id, int hp) : Elf(id, hp), Archer(id, 42) {};

    unitid id() const { return Elf::id(); }
    int hp() const { return Elf::hp(); }
private:
    int dataElfArcher;
};

int main() {
    ElfArcher* elfArcher = new ElfArcher((unitid) 12, 100);
    Elf* elf = dynamic_cast<Elf*>(elfArcher);
    Archer* archer = dynamic_cast<Archer*>(elfArcher);

    std::cout << "ElfArcher*: " << elfArcher << std::endl;
    std::cout << "-> cast to Elf*   : " << elf << std::endl;
    std::cout << "-> cast to Archer*: " << archer << std::endl << std::endl;
    std::cout << "Archer HP (должно быть 42): " << archer->hp() << std::endl << std::endl;

    elfArcher = dynamic_cast<ElfArcher*>(elf);
    std::cout << "ElfArcher* from Elf*: " << elfArcher << std::endl;
    std::cout << "ElfArcher HP: " << elfArcher->hp() << std::endl;
      
    elfArcher = dynamic_cast<ElfArcher*>(archer);
    std::cout << "ElfArcher* from Archer*: " << elfArcher << std::endl;
    std::cout << "ElfArcher HP: " << elfArcher->hp() << std::endl << std::endl;

    elfArcher = (ElfArcher*)archer;
    std::cout << "(ElfArcher*)archer: " << elfArcher << std::endl;
    ElfArcher* elfArcher1 = (ElfArcher*)(void*)archer;
    std::cout << "(ElfArcher*)(void *)archer: " << elfArcher1 << std::endl;
    std::cout << "ElfArcher HP (ожидалось UB, но его нет): " << elfArcher1->hp() << std::endl;

    return 0;
}
