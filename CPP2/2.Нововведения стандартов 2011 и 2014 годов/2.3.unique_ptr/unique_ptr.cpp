// https://eax.me/cpp-smart-pointers/
// C++14 (std::make_unique)
#include <memory>
#include <iostream>

// https://stackoverflow.com/a/21174979/1565238
template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del>
static_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d,
        std::move(p.get_deleter()));
}

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del>
dynamic_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    if(Derived *result = dynamic_cast<Derived *>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result,
            std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

class Base {
public:
    Base(int num): num(num) {};

    virtual void sayHello() {
        std::cout << "I'm Base #" << num << std::endl;
    }

    virtual ~Base() {
        std::cout << "~Base #" << num << std::endl;
    }

protected:
    int num;
};

class Derived: public Base {
public:
    Derived(int num): Base(num) {}

    virtual void sayHello() {
        std::cout << "I'm Derived #" << num << std::endl;
    }

    virtual ~Derived() {
        std::cout << "~Derived #" << num << std::endl;
    }
};

void testUnique() {
    std::cout << "=== testUnique begin ===" << std::endl;

    auto derived = std::make_unique<Derived>(1);
    derived->sayHello();

    std::unique_ptr<Base> base = std::move(derived);
    base->sayHello();

    auto derived2 = static_unique_ptr_cast<Derived>(std::move(base));
    derived2->sayHello();

    std::unique_ptr<Base> base2 = std::make_unique<Derived>(2);
    base2->sayHello();

    std::cout << "=== testUnique end ===" << std::endl;
}

void testShared() {
    std::cout << "=== testShared begin ===" << std::endl;

    auto derived = std::make_shared<Derived>(1);
    derived->sayHello();

    auto base = std::static_pointer_cast<Base>(derived);
    base->sayHello();

    auto derived2 = std::static_pointer_cast<Derived>(base);
    derived2->sayHello();

    std::shared_ptr<Base> base2 = std::make_shared<Derived>(2);
    base2->sayHello();

    std::cout << "=== testShared end ===" << std::endl;
}

int main() {
    testUnique();
    testShared();
}