#include <iostream>
#include "header.hpp"

extern void file2() {
    std::cout << "file2.cpp\n"; 
    std::cout << "- foo   : " << (void *)foo << "\n";
    std::cout << "- bar   : " << (void *)bar << "\n";
    std::cout << "- foobar: " << (void *)foobar << "\n";
}