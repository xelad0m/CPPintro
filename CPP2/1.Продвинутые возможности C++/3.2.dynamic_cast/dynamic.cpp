#include <iostream>

struct Base { virtual ~Base() { } };
struct Derived1 : virtual Base { };
struct Derived2 : virtual Base { };
struct Derived3 : Derived1, Derived2 { };

// Представление в памяти:
// [base]: [base]
// [Derived1]: [Derived1][base];
// [Derived2]: [Derived2][base];
// [Derived3]: [Derived1][Derived2][base];

int main() {
    using namespace std;
    Base* b = new Derived3();
    Derived3* recovery3 = dynamic_cast<Derived3*>(b);
    Derived2* recovery2 = dynamic_cast<Derived2*>(b);
    Derived1* recovery1 = dynamic_cast<Derived1*>(b);

    void* BasePtr = dynamic_cast<void*>(b);
    cout << "Base* " << b << endl;
    cout << "dynamic_cast<void*> "<<BasePtr<<endl;
    cout << "dynamic_cast<Derived3*> " << recovery3 << endl;
    cout << "dynamic_cast<Derived2*> " << recovery2 << endl;
    cout << "dynamic_cast<Derived1*> " << recovery1 << endl;   

    cout << "\ndynamic_cast<void*>(recovery1) " << dynamic_cast<void*>(recovery1) << endl;   
    cout << "\ndynamic_cast<void*>(recovery2) " << dynamic_cast<void*>(recovery2) << endl;   
    cout << "\ndynamic_cast<void*>(recovery3) " << dynamic_cast<void*>(recovery3) << endl;   

    return 0;
}
