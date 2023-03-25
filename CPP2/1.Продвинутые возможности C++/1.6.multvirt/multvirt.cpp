#include <iostream>

struct unitid {
    explicit unitid( int i = 0 ) : id(i) {}
    int id;
};
struct Unit {
    Unit(unitid id, int hp): hp_(hp) {
    	std::cout << "Unit constructor call" << std::endl;
    };
    int hp() const { return hp_; }
private:
    int    hp_;
};
struct Elf: virtual Unit {
    explicit Elf(unitid id)
        : Unit(id, 100) {
    	std::cout << "Elf constructor call" << std::endl;
    }
};
struct Archer: virtual Unit {
    explicit Archer(unitid id)
        : Unit(id, 120) {
    	std::cout << "Archer constructor call" << std::endl;
    }
};
struct ElfArcher: Elf, Archer {
    explicit ElfArcher(unitid id)
        : Unit(id, 150)
        , Elf(id)
        , Archer(id) {}
};

int main() {
	ElfArcher * ea = new ElfArcher((unitid) 42);

	std::cout << "ElfArcher HP: " << ea->hp() << std::endl;

    return 0;
}
