#include <iostream>
#include <string>
#include <exception>
 
int main()
{
    std::cout << "Default constructor: " <<  noexcept(std::string()) << "\n";
    std::string s = "str";
    std::cout << "Copy constructor:    " <<  noexcept(std::string(s)) << "\n";
    std::cout << "Move constructor:    " <<  noexcept(std::string(std::move(s))) << "\n";

    std::cout << "op =:                " <<  noexcept(s = "asd") << "\n";
    std::cout << "Move op =:           " <<  noexcept(std::move("asd")) << "\n";

    std::cout << "size():              " <<  noexcept(s.size()) << "\n";
    std::cout << "clear():             " <<  noexcept(s.clear()) << "\n";
    
    // std::string s1 = new std::string("str");
    std::cout << "delete:              " <<  noexcept(delete &s) << "\n";

    return 0;
}