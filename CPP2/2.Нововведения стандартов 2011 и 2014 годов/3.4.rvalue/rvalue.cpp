#include <iostream>
#include <type_traits>

template <typename T>
void summator(T && a, T && b) { a += b; }



struct A {
    A() = default;
    A(const A&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A& operator=(const A&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    A(A&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A& operator=(A&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
};



void Print(const int& x) {
  std::cout << x << " L-value overload\n";
}

void Print(int&& x) {
  std::cout << x << " R-value overload\n";
}

// Выберите функции, при вызове которых обязательно происходит перемещение объекта String, 
// т.е. вызов перемещающего конструктора (у класса String он определен).
// Получается
// - должен возвращаться объект, а не ссылка/rv-ссылка
// - ...
// Короче, я понял, что я ничего не понял...
struct String
{
    // все объявленные ниже методы уже реализованы
    String() { };
    String(String const& s) { };
    String & operator=(String const& a) { return *this; };
    ~String() { };

    // перемещающий конструктор
    String(String && s)
    {
        std::cout << "Move Constructor" << std::endl;
    }

    // перемещающий оператор присваивания
    String& operator =(String && s)
    {
        std::cout << "Move Operator = " << std::endl;
        return *this;
    }
 
};

// при вызове этих функции в операциях присваивания будут вызываться
String & fun1(String & s)
{
    return s; // просто конструктор (это локальная переменная)
}

String && fun2(String & s)
{
    return std::move(s); // op= перемещ.
}

String fun3(String & s)
{
    return std::move(s); // к.перемещ. + op= перемещ.
}

String fun4(String s)
{
    return std::move(s); // к.перемещ. + op= перемещ.
}

String fun5(String s)
{
    return std::forward<String>(s); // к.перемещ. + op= перемещ.
}

String && fun6(String && s)
{
    return std::move(s); // op= перемещ.
}

String fun7(String && s)
{
    return s; // op= перемещ.
}

int main() {
    int a = 1, b = 2;
    summator <int&> (a, b); // Правило склейки & (a и b - lvalue ссылки) и && (параметры функции) -> &
    summator <int> (1, 2);  // Правило склейки && (1 и 2 - rvalue ссылки) и && (параметры функции) -> &&
    std::cout << a << std::endl; // Значение a изменилось, поскольку функция работала с параметрами как с lvalue ссылками;


    A a1, b1;
    b1 = a1;
    b1 = static_cast<A&>(a1);
    b1 = static_cast<A&&>(a1);
    b1 = std::move(a1);

    // 
    Print(6);// 6 R-value overload
    int x = 5;
    Print(x);// 5 L-value overload
    typedef std::remove_reference<int&>::type RV;  
    Print(static_cast<RV>(x));// 5 R-value overload

    String str, str2;
    std::cout <<"fun1" << std::endl;
    str2 = fun1(str);
   
    std::cout <<"fun2" << std::endl;  
    str2 = fun2(str);
   
    std::cout <<"fun3" << std::endl;
    str2 = fun3(str);
   
    std::cout <<"fun4" << std::endl;
    str2 = fun4(str);
   
    std::cout <<"fun5" << std::endl;
    str2 = fun5(str);
   
    std::cout <<"fun6" << std::endl;
    str2 = fun6(String());
   
    std::cout <<"fun7" << std::endl;
    str2 = fun7(String());

    return 0;
}
