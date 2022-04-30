/*В первом уроке вы реализовали простой шаблон ValueHolder, в этом задании мы используем его чтобы написать класс Any 
(интересно, что не шаблонный), который позволяет хранить значения любого типа! Например, вы сможете  создать массив 
объектов типа Any, и сохранять в них int-ы, double-ы или даже объекты Array. Подробности в шаблоне кода.

Hint: в нешаблонном классе Any могут быть шаблонные методы, например, шаблонный конструктор.

Для реализации вам может потребоваться оператор dynamic_cast.

С++ предоставляет и более простой способ узнать конкретный класс по указателю (или ссылке) на базовый класс. 
Для этого можно использовать оператор dynamic_cast. Например, если у вас есть указатель Expression *, и вы хотите 
узнать, указывает ли этот указатель на самом деле на объект Number, то сделать это можно так:

Expression *expression = parse(code);
Number *number = dynamic_cast<Number *>(expression);
if (number)
    std::cout << "It's a number" << std::endl;
else
    std::cout << "It is not a number" << std::endl;

Если expression действительно указывает на объект Number (или на один из его наследников, но в нашем примере их нет), 
то оператор dynamic_cast<Number *> вернет правильный указатель. Если expression указывает не на класс Number, то будет 
возвращен нулевой указатель. Т. е. если в переменной number хранится нулевой указатель, значит expression не указывает 
на Number на самом деле.

Для правильной работы оператора dynamic_cast в нашем примере требуется, чтобы класс Expression был полиморфным, т. е. 
в нем должна быть как минимум одна виртуальная функция (например, деструктор). Стандарт определяет работу dynamic_cast 
и с не полиморфными типами, но в этом случае никаких проверок типа времени исполнения выполняться не будет - часто, 
это не то, что требуется.

Если передать оператору dynamic_cast нулевой указатель, то он просто вернет нулевой указатель нужного типа, поэтому 
проверять указатель перед передачей в dynamic_cast не нужно.*/

// типа как boost::any


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
    ValueHolder(const T& other) : data_(other) { }
    ICloneable* clone() const { return new ValueHolder(data_); }
};

struct Any
{
    ICloneable* holder_;        // не ValueHolder, ибо он шаблонный

    // нешаблонные вещи
    Any() { holder_ = nullptr; }
    Any(const Any& other) 
    {   
        if ( (this != &other) && (other.holder_) )
            holder_ = other.holder_->clone();
    }
    Any& operator=(const Any& other) 
    {   
        if ( (this != &other) && (other.holder_) )
        {
            delete holder_;
            holder_ = other.holder_->clone();
        }
        return *this;
    }   
    virtual ~Any() { delete holder_; }

    // шаблонный конструктор от одного параметра:
    //    Any i(10); // i хранит значение 10
    template <typename T>
    Any(const T& value = T())
    { holder_ = new ValueHolder<T>(value); }
 
    // шаблонный метод cast:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    template <typename T>
    T* cast()
    {   
        ValueHolder<T> * ptr = dynamic_cast < ValueHolder<T> * > (holder_);
        return  (ptr) ? &ptr->data_ : nullptr;
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
    Any empty;
    cout << empty.cast<int>() << endl;      // 0

    Any i(10);
    cout << *(i.cast<int>()) << endl;       // 10

    Any copy(i);    
    cout << *copy.cast<int>() << endl;      // 10
    empty = copy;   
    cout << *empty.cast<int>() << endl;     // 10
    empty = 0;      
    cout << *empty.cast<int>() << endl;     // 0

    int *iptr = i.cast<int>(); 
    cout << *iptr << endl;                  // 10
    char *cptr = i.cast<char>();
    printf("%p\n", cptr);                     

    Any empty2;
    int *p = empty2.cast<int>(); 
    printf("%p\n", p);                     


    return 0;
}