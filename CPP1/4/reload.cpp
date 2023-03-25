#include <iostream>
#include <cstring>


// 1
void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }

// 2
struct String {
    /* Реализуйте этот конструктор */
	String(const char *str = "")
    {
        size = strlen(str);                         // можно без this
        char *new_str = new char [size + 1];        // указатель на строку длины size + 1
        strcpy(new_str, str);                       // вместо цикла, копирует \0 тоже
        this->str = new_str;                        // нельзя без this (указатель)
    }

    char & at(size_t idx)       { return str[idx]; }
    char   at(size_t idx) const { return str[idx]; }
    /* ... */
    size_t size;
    char *str;
};

// 3
void promotion(char &) { std::cout << "char" << std::endl; }
void promotion(int  &) { std::cout << "int"  << std::endl; }
void promotion(long &) { std::cout << "long" << std::endl; }

int main()
{
    // 1
    // захаржкоденные целые по умолчанию int, их нельзя привести к char 
    // без потери точности
    // foo(97);        // error: call of overloaded ‘foo(int)’ is ambiguous

    foo('a');       // char

    // 2
    String greet("Hello");
    char ch1 = greet.at(0);                         // this != const

    String const const_greet("Hello, Const!");
    char const &ch2 = const_greet.at(0);            // у конст.объектов могут быть вызваны только конст.методы  
    // & не породит несоответствие возвращаемого типа, это будет ссылка на char

    // 3
    short sh = 10;
    // promotion(sh);      // не скомпилируется, т.е. преобразование адреса в int& будет захватывать больший участок памяти 
                        // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    // преобразование short в int безопасно, но преобразование  short* в int* небезопасно  поскольку означает, 
    // что с областью памяти, выделенной под short мы будем обращаться как будто она выделена под int


    return 0;
}