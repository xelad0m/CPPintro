#include <iostream>

template<class T>
void foo(T const * p) { std::cout << *p << std::endl; };

void foo(char const * p) = delete;

int main() 
{   
    int const i = 42;
    double const d = 3.14;
    std::string const s = "Hello";

    foo(&i);
    foo(&d);
    foo(&s);

    // char const c = 'a';
    // foo(&c); // error: use of deleted function

    return 0;   
}