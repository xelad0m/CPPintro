#include <iostream>

class A {
public:
    void foo() {
        std::cout << "A\n";
    }
};

class B : public A {
public:
    B(int id) {
        this->id = id;
    }
    void foo() {
        std::cout << "B\n";
    }
    int id;
};


class C : public A {
public:
    C(int id) {
        this->id = id;
    }
    void foo() {
        std::cout << "C" << id << "\n";
    }
    int id;
};

// с поддержкой пользовательского преобразования типа
class D : public A {
public:
    D(int id) {
        this->id = id;
    }
    void foo() {
        std::cout << "D" << id << "\n";
    }
    operator D() const { return D { id }; }
    int id;
};

int main() {
    A* b = new B(1);
    A* c = new C(2);

    b->foo();                       // A
    static_cast<C*>(b)->foo();      // C1

    c->foo();                       // A
    static_cast<C*>(c)->foo();      // C2

    D d = static_cast<D>(3);        // D3
    d.foo();

    return 0;
}