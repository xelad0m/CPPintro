#include <iostream>

int doublecmp(void const * a, void const * b) {
    double da = *static_cast<double const *>(a);
    double db = *static_cast<double const *>(b);
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

// p - указатель на первый элемент, q - указатель на пространство за концом массива
void sort(double * p, double * q) {
    std::qsort(p, q - p, sizeof(double), &doublecmp);
}

void print_double_array(double * p, double * q) {
    int length = q - p;
    for (int i = 0; i < length; i++) {
        std::cout << *(p + i) << " ";
    }
    std::cout << "\n";
}

int main() {
    size_t size = 10;
    double a[size] = {5.4, 3.6, 2.2, 9.1, 7.3, 5.3, 3.1, 8.7, 4.4, 0.4};

    std::cout << "Raw array:\n";
    print_double_array(a, a + size);
    
    sort(a, a + size);
    std::cout << "Sorted array:\n";
    print_double_array(a, a + size);

    return 0;
}
