#include <iostream>

int main() {
    
    int array[] = {1, 4, 9, 16, 25, 36, 49};
    
    // по ссылке (удвоение элементов)
    for (int & x : array) {
        x *= 2;
    }

    for (int & x : array) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    int sum = 0;
    // по значению (сумма элементов)
    for (int x : array) {
        sum += x;
    }
    std::cout << "sum=" << sum << "\n";

    return 0;
}