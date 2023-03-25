#include <iostream>
#include <string>

std::string f() {
    return "test";
}

int main() {
    const std::string& ttt = f();  
    std::cout << ttt << std::endl;
    // object returned by f is deleted here
}