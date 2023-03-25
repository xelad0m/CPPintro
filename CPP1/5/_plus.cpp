#include <iostream>

int main() {
    char a = 'a';
    std::cout << a << std::endl;        // char
    std::cout << +a << std::endl;       // код символа


    int i = 42;
    const int & li = i;

    std::cout << li << std::endl;      // i


    
    int * I [10];
    for (int i=0; i<10;++i)
        I[i] = new int (i);
    
    for (int i=0; i<10;++i)
        std::cout << *I[i] << " ";

    return 0;
}