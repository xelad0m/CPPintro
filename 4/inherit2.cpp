/* Вам дан класс Foo:

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};

Как видно, создатель класса не хотел чтобы его использовали и "спрятал" конструктор класса. 
Но вам очень нужен объект этого класса, чтобы передать его в функцию foo_says:

void foo_says(const Foo& foo) { foo.say(); }

В этом задании вам нужно реализовать функцию get_foo (сигнатура которой намерено не приводится в задании полностью, 
вам нужно подумать и вывести ее самостоятельно) так, чтобы следующий код компилировался и работал:

foo_says(get_foo(msg));

Где msg — произвольная C-style строка. */


#include <iostream>
#include <string>
using namespace std;

// дано
struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};


// типа неявное приведение типа
void foo_says(const Foo& foo) { foo.say(); }
// решение 1
struct DerivedFromFoo : Foo {
    DerivedFromFoo(const char *msg)         // конструктор наследника
    : Foo(msg)                              // имеет доступ к protected родителя (но не private)
    {}
};

DerivedFromFoo get_foo(const char *msg) {
    DerivedFromFoo dFoo(msg);
    return dFoo;                            // возвращается экземпляр типа DerivedFromFoo, но при передаче в функцию foo_says()
}                                           // происходит неявное приведение типа DerivedFromFoo -> Foo при копировании аргумента (наверно, я уже хз)


// когда get_foo возвращает временный объект, она на самом деле копирует его в 
// зарезервированное под возвращаемое значение место на стеке.
// Затем мы выходим из get_foo, все локальные переменные на стеке уничтожаются, 
// а скопированное возвращаемое значение либо записывается в соответствующую переменную, 
// либо теряется. За одним исключением: если мы создаем константную ссылку на временный объект, 
// время жизни временного объекта продлевается до времени жизни константной ссылки, что здесь и происходит. 

string f() { return "const link &"; }            // "abc" убирается со стека с последей скобкой

void g() {
    // string& s = f();                // ... и сюда уже пришел бы мусор, если бы компилятор не сказал 
    //                                 // error: cannot bind non-const lvalue reference of type ‘std::string&’ ... to an rvalue of type ‘std::string’

    const string& s = f();             // а если ссылка константная, то все ОК
    // string s = f();                     // речь только про ссылки, так просто скопируется конструктором копирования
    cout << s << endl;
}

int main()
{   
    const char * msg = "Hello!";
    // Foo foo(msg);                           // error: ‘Foo::Foo(const char*)’ is protected within this context  
    foo_says(get_foo(msg));                 // OK

    g();

    return 0;
}