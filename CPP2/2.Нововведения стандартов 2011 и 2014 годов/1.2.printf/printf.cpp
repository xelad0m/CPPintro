#include <iostream>
#include <cassert>

// база рекурсии: нет аргументов, значит не должно оставаться и 
// необработанных упр. символов форматной строки (кроме варианта %%)
void mprintf(const char* format)
{
    while (*format)
    {
        if (*format == '%' && *(++format) != '%')
        {
            assert(!"unhandled format specifier");
        }
        std::cout << *format++;
    }
}

// Паттерн шаблона с переменным числом аргументов
// - тут форматная строка не проверяет соотвествие аргументов и не 
// умеет настраивать точность как `printf`, просто любое сочетание
// `%*` значит выводится следующий аргумент
template<typename T, typename... Args>
void mprintf(const char* format, T value, Args... args)
{
    while (*format)
    {
        if (*format == '%' && *(++format) != '%')
        {
            std::cout << value;
            return mprintf(++format, args...);
        }
        std::cout << *format++;
    }
    assert(!"extra arguments provided to mprintf");
}

int main() 
{   
    // подстановочные символы после % любые
    mprintf("%s, %s!\ni = %f\nf = %k\np = %a%%\n", "Hello", "world", 42, 3.14, 100);

    return 0;   
}