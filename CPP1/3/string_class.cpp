
// Компилятору C++ позволено выполнять оптимизации, связанные с удалением ненужных вызовов конструктора 
// копирования (copy elision) при определенных условиях, даже если конструктор копирования содержит сайд 
// эффекты (например, вывод в std::cout), поэтому на большинстве современных компиляторов конструктор 
// копирования не будет вызван ни в одной из указанных ситуаций. Однако, компилятор не обязан выполнять эту оптимизацию.

// В каких из приведенных ниже ситуаций может быть вызван конструктор копирования класса String:
#include <iostream>
#include <cstring>

struct String
{
    size_t size;
    char* str;

    /* Конструктор пустой*/
    String()
    : size(0), str(new char[size+1])
    {}

    /* Конструктор с параметрами*/
    String(size_t s, const char *str)
    : size(s), str(new char[size+1])
    {
        size = strlen(str);                         
        char *new_str = new char [size + 1];        
        strcpy(new_str, str);                       
        this->str = new_str;                      
    }

    /* Второй конструктор */
	String(size_t n, char c)
    {
        size = n;                   
        char *new_str = new char [size + 1];        
        for (size_t i = 0; i < size; ++i)
            *(new_str + i) = c;

        new_str[size] = '\0';
        this->str = new_str;
    }

    void  swap(String & other) {
        std::swap(size , other.size);     
        std::swap(str , other.str);
    }

    // Конструктор копирования
    String(String  const& other)                        
    : size(other.size), str(new char [other.size + 1])   // новый
    {
        // std::cout << "COPY: String(String  const& other)" << std::endl;
        
        for (size_t i = 0; i != size; ++i)
            str[i] = other.str[i];                   // копируем
        str[size] = '\0';
    }

    // Конструктор присваивания
    String & operator =(const String& other)
    {
        // std::cout << "=: String & operator =(const String& other)" << std::endl;

        if (this != &other)                 
            String(other).swap(*this);    
        return *this;
    }
};


int main()
{
    String a;
    String b = a;   // (copy)constructor

    String * p = &a;
    String * p1 = &b;
    *p = *p1;       // (=)constructor + (copy)constructor

}

// 1. NO (=)constructor, NO (copy)constructor
// String spaces(size_t n) 
// {
//     const String s(n, ' ');
//     return s;
// }

// int main() 
// {
//     std::cout << spaces(10).str << "\n";
//     return 0;
// }

// 2. (=)constructor + (copy)constructor

// int main() 
// {
//     String ten_spaces;
//     ten_spaces = String(10, 'f');
//     std::cout << ten_spaces.str << "\n";
//     return 0;
// }

// 3. NO (=)constructor, NO (copy)constructor

// void foo(String str) 
// {
//     std::cout << str.str << "\n";
// }

// int main() 
// {
//     foo(String(10, ' '));
//     return 0;
// }

// 4. invalid initialization of reference of type ‘const String&’ from expression of type ‘const char [11]’

// void bar(const String &str) 
// {
//     std::cout << str.str << "\n";
// }

// int main() 
// {
//     // тип не приводится, ниче не работает
//     bar("          "); // ten spaces;
//     return 0;
// }
