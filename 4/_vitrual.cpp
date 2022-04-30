#include <iostream>
#include <string>
using namespace std;

// 1
struct A
{
   virtual void foo() = 0;
   virtual ~A() {}
};

struct B : A
{
   B() { /*foo();*/ }
   void foo() { std::cout << "B" << std::endl; }
   ~B() { foo(); }
};

struct C : B
{
   C() { /*foo();*/ }
   void foo() { std::cout << "C" << std::endl; }
   ~C() { foo(); }
};

struct D : C
{
   D() { /*foo();*/ }
   void foo() { std::cout << "D" << std::endl; }
};

// 2
struct  Person {
    Person(string  const& nm) : name_(nm) { }
    virtual  string  name() const {return  name_ ;}
    virtual ~Person() { std::cout << "~Person()" << std::endl;}
private:
    string name_;
};

struct  Teacher : Person {
    Teacher(string  const& nm) : Person(nm)
    { std::cout  << name () << std::endl; }                                 // вызовем в конструкторе вирт.метод
};

struct  Professor : Teacher {
    Professor(string  const& nm) : Teacher(nm) { }
    string  name() const {return "Prof. " + Person::name();}                        
};


int       main()
{
    // 1
    A * object = new D();
    delete object;
    
    // 2
    Professor p("Stroustrup"); // "Stroustrup" (из базового класса)
    return 0;
}