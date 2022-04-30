/*Шаблонные классы можно наследовать. Реализуйте шаблонную структуру ValueHolder с одним типовым параметром 
T, унаследованную от интерфейса ICloneable. Интерфейс ICloneable содержит всего один виртуальный метод 
ICloneable* clone() const, который должен вернуть указатель на копию объекта, на котором он был вызван 
(объект должен быть создан в куче). Шаблон ValueHolder, как говорит его название, хранит всего одно значение 
(назовите его data_) типа T (для типа T определен конструктор копирования). Не делайте поле data_ закрытым 
(поэтому в данном случае мы явно пишем, что ValueHolder должна быть структурой). */

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.


#include <iostream>
using namespace std;

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : ICloneable
{
    T data_;
    ValueHolder(const T& other) 
    : data_(other)                  // при такой инициализации вызывается К.копирования (а это он и есть)
    { }                             
    // { data_ = other }            // при такой инициализации вызывается оп.присваивания (не наш случай)
    
    ValueHolder* clone() const      // также проходит тесты
    // ICloneable* clone() const    // указатель к родительскому типу приводится автоматически
    {                               // как то связано с тем, что виртуальные методы определяются по типу this
        return new ValueHolder(data_); 
    }
};

class MyInteger {
    int i;
public:
    MyInteger() { i = 0; }
    MyInteger(int const value) { i = value; }
    MyInteger(const MyInteger& value) { i = (int)value; }
    virtual ~MyInteger() { }
    
    MyInteger& operator= (const MyInteger& value) 
    {
        if (this != &value)
            i = (int)value;
        return *this;
    }
    
    operator int() const { return i; }
};

int main()
{   
    ICloneable* a = new ValueHolder<int>(10);
    cout << ((ValueHolder<int>*)a)->data_ << " " << a << endl;
    ICloneable* b = a->clone();
    delete a;
    cout << ((ValueHolder<int>*)b)->data_ << " " << b << endl;
    delete b;

    MyInteger* value = new MyInteger(20);
    ICloneable* a_obj = new ValueHolder<MyInteger>(*value);
    cout << (int)(((ValueHolder<MyInteger>*)a_obj)->data_) << " " << a_obj << endl;
    ICloneable* b_obj = a_obj->clone();
    delete a_obj;
    cout << (int)(((ValueHolder<MyInteger>*)b_obj)->data_) << " " << b_obj << endl;
    delete b_obj;

    return 0;
}