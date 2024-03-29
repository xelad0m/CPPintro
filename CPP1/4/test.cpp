#include <iostream>
#include <string>
using namespace std;
// Сейчас со всем этим разберемся, но перед этим вспомним следующие правила:
//    Класс всегда имеет доступ к своим (не наследуемым) членам.
//    Доступ к члену класса основывается на его спецификаторе доступа.
//    Дочерний класс имеет доступ к унаследованным членам родительского класса на основе спецификатора доступа этих членов в родительском классе.



// Если в базовом классе виртуальная функция определена как private, то в производном классе её можно переопределить как public.
struct A
{
private:
    virtual void foo() { cout << "A::foo()" << endl; }
};

struct B : private A
{
public:
    virtual void foo() { cout << "B::foo()" << endl; }
};
// Нет, переопределения не произойдет, просто новый метод



/* У интерфейсов нет таблиц виртуальных методов. */
struct  IConvertibleToString {
    virtual ~IConvertibleToString () {}
    virtual  std::string  toString () const = 0;
};
/* Не верно, таблица есть
Vtable for IConvertibleToString
IConvertibleToString::_ZTV20IConvertibleToString: 5 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI20IConvertibleToString)
16    0
24    0
32    (int (*)(...))__cxa_pure_virtual
*/



// Чистый виртуальный метод с определением — это не то же самое, что обычный виртуальный метод.
struct  C {
    virtual  void  foo() = 0;
};
    
void  C::foo() { cout << "C::foo()" << endl; } 
   
struct  D : C {
// private:
    void  foo() { C::foo(); }
};
// Верно, не идет в VMT, адрес вызова хардкодится



// Производные классы не видят protected-предков своего (непосредственного) базового класса, если они унаследованы от базового класса с модификатором private.
struct E : D {

};
// Не верно, видят. Модификатор наследования не влияет на то, как дочерний класс получает доступ к членам родительского класса!



// Если в базовом классе виртуальная функция определена как public, то в производном классе её можно переопределить как private.
// struct A
// {
// public:
//     virtual void foo() { cout << "A::foo()" << endl; }
// };

// struct B : A
// {
// private:
//     virtual void foo() { cout << "B::foo()" << endl; }
// };
// // Получается, что можно



// Производные классы не видят private-предков своего базового класса.
// Производные классы не могут переопределять private-виртуальные методы базового класса, если они унаследованы от базового класса с модификатором private. 

int main()
{
    // A a; B b;
    // a = b; 
    // a.foo(); // virtual void A::foo()’ is private within this context

    // A a; B b;
    // a = b; 
    // b.foo(); // ‘virtual void B::foo()’ is private within this context




    D d;
    d.foo();

    return 0;
}

/*Путем долгого тыканья:
    ДА Если в базовом классе виртуальная функция определена как public, то в производном классе её можно переопределить как private.
        (как хошь так и определяй, если имеешь доступ)
    ДА Если в базовом классе виртуальная функция определена как private, то в производном классе её можно переопределить как public.
        (как хошь так и определяй, если имеешь доступ)
    ДА Чистый виртуальный метод с определением — это не то же самое, что обычный виртуальный метод.
        (это статический метод по сути, а не динамический)
    нет Производные классы не видят protected-предков своего (непосредственного) базового класса, если они унаследованы от базового класса с модификатором private.
        (производные private наследники имеют эксклюзивный доступ, а protected - только производные имет доступ => они то как раз и имеют, а больше никто)
    нет У интерфейсов нет таблиц виртуальных методов.
        (у всех классов с виртуальными методами есть)
    нет Производные классы не могут переопределять private-виртуальные методы базового класса, если они унаследованы от базового класса с модификатором private.
        (как раз только производные и имеют доступ к базовому если наследовались private)
    ДА Производные классы не видят private-предков своего базового класса. 
        (кто private наследовался, тот только и имеет доступ)
*/