#include <iostream>
#include "header.hpp"

extern void file3() {
    std::cout << "file3.cpp\n"; 
    std::cout << "- foo   : " << (void *)foo << "\n";
    std::cout << "- bar   : " << (void *)bar << "\n";
    std::cout << "- foobar: " << (void *)foobar << "\n";
}

int main() {

    file1();
    file2();
    file3();
    return 0;
}