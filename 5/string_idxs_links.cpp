/* 
В этой задаче вам требуется реализовать оператор [] для уже известного вам класса String. Однако на этот
раз оператор должен реализовывать нестандартное поведение: оператор нужно реализовать таким образом, чтобы 
для объекта str класса String можно было писать str[i][j] и это выражение возвращало подстроку начинающуюся 
в позиции i (считая с 0) и заканчивающуюся в позиции j (не включая).

Например:
String const hello("hello");
String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"

Обратите внимание, что i может равняться j, в этом случае результатом должна быть пустая строка. Гарантируется, 
что i никогда не будет больше j, и они не будут выходить за пределы длины строки.
*/

#include <iostream>
#include <cstddef>  // size_t
#include <cstring>  // strlen, strcpy
using namespace std;

struct String {
    // конструктор с параметрами
	String(const char *str_ = "")
    {
        size = strlen(str_);                         // можно без this
        char *new_str = new char [size + 1];        // указатель на строку длины size + 1
        strcpy(new_str, str_);                       // вместо цикла, копирует \0 тоже
        this->str = new_str;                        // нельзя без this (указатель)
        // delete [] str_;
    }
    
    // конструктор с параметрами
	String(size_t n, char c)
    {
        size = n;                   
        char *new_str = new char [size + 1];        
        for (size_t i = 0; i < size; ++i)
            *(new_str + i) = c;

        new_str[size] = '\0';
        this->str = new_str;
    }

    // конструктор копирования
    String(const String &other) 
    {   
        char *new_str = new char [other.size + 1];
        strcpy(new_str, other.str);
        this->str = new_str;
    }

    // деструктор
	~String()
    {
        delete [] str;
    }
    
    // оператор присваивания
    String &operator=(const String &other);
    
    // метод
	void append(const String &other)
    {   
        size_t _size = size;                        // свой исходный размер без \0
        size = size + other.size;                   // новый размер без \0
        char *new_str = new char [size + 1];        // +1 для \0

        strcpy(new_str, this->str);
        strcpy(new_str + _size, other.str);         // условный -1 для \0

        new_str[size] = '\0';                       // в тестах size + 1 дает ошибку (тут тоже должен по идее)

        delete [] this->str;                        // освободить занимаемую память
        this->str = new_str;                        // записать новую строку
    }

    // агрегированный класс - член класса (member)
    struct Proxy                                    
    {
        char *str_;
        int idx;                                    // сколько уже отчикали
        
        // конструктор с индексом
        Proxy(char const *substr = "", int idx = 0)
        {   
            this->idx = idx;                        
            char *new_str = new char [strlen(substr) + 1];        
            strcpy(new_str, substr);                // копирует \0 тоже
            this->str_ = new_str;     
        }
        ~Proxy() 
        { 
            delete [] this->str_; 
        }
        
        // обратная история
        String operator[](int const &index) const
        {                      
            int size_ = index - this->idx;
            char *new_str_ = new char [size_ + 1];       
            
            for (size_t i = 0; i < size_; ++i)
                *(new_str_ + i) = *(this->str_ + i);
            new_str_[size_] = '\0';
            
            String result(new_str_);
            String * presult = &result;
            delete [] new_str_;                      

            return result;
        }
    };

    // вариант с возвратом по ссылке (валится почему-то, видимо что-то с конст.ссылками и т.п. премудростью)
    // вот оно что, тут то и нужен "умный указатель" !
    Proxy operator[](int const& index) const {
        int size = strlen(str) - index;                         
        char *new_str = new char [size + 1];    

        for (size_t i = 0; i < size; ++i)
            *(new_str + i) = *(this->str + index + i);
        new_str[size] = '\0';

        Proxy proxy(new_str, index);               // запомнить индекс для среза
        Proxy * pproxy = &proxy;
        delete [] new_str;

        return proxy;
    }

	size_t size;
	char *str;
};


int main()
{
    // 1
    const char * cstr = "C-style string";
    String str(cstr);
    std::cout << str.str << std::endl;

    // 2
    String str_(10, 'f');
    std::cout << str_.str << std::endl;

    // 3
    String s1("Hello,");
    String s2(" world!");

    s1.append(s2);                      
    std::cout << s1.str << std::endl;   // Hello, world!

    String s("Hello");
    s.append(s);                        
    std::cout << s.str << std::endl;    // HelloHello

    // 4
    String other = s;
    std::cout << other.str << std::endl;// HelloHello

    // 5
    String const hello("hello");
    String const hell = hello[0][4];    
    String const ell  = hello[1][4];    
    String const empty  = hello[3][3]; 

    std::cout << hell.str << std::endl; // hell
    std::cout << ell.str << std::endl;  // ell
    std::cout << empty.str << std::endl;  // ''

    return 0;
}