#include <iostream>

struct Unit {
    virtual Unit * GetSelf() {
        std::cout << "Get unit" << std::endl;
        return this;
    }
    virtual ~Unit() {};
private:
    int unit_field_ = 0;
};

struct Elf : virtual Unit {
    Elf * GetSelf() override {
        std::cout << "Get elf" << std::endl;
        return this;
    }
    virtual ~Elf() {};
private:
    int elf_field_ = 1;
};

int main() {
    Elf * elf = new Elf;
    Unit * unit = elf;
    void * override_ptr = unit->GetSelf();
    std::cout << "Ptrs are equal without offset " << (override_ptr == elf) << std::endl;
    std::cout << "Ptrs are equal with    offset " << (override_ptr == unit) << std::endl;
    return 0;
}
