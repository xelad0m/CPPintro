#include <iostream>
#include <cassert>

// база рекурсии
void print_values(std::ostream & os) { };

// Шаблон с переменным числом аргументов
template<typename T, typename... Args>
void print_values(std::ostream & os, T const & value, Args const &... args)
{
    os << typeid(value).name() << ": " << value << "\n";
    return print_values(os, args...);
}


template <typename... Args>
void print_values_comma(std::ostream& os, const Args&... args)
{
    int unused[sizeof...(Args)] = { (os << typeid(args).name() << ": " << args << std::endl, 0)... };
}

int main() 
{   
    print_values(std::cout, 0, 3.5, "Hello");
    print_values_comma(std::cout, 0, 3.5, "Hello");

    return 0;   
}