#include <iostream>

// p - указатель на первый элемент, q - указатель на пространство за концом массива

template <typename T>
void sort(T * p, T * q, bool (*cmp)(T, T)) {
    for (T * m = q; m != p; -- m)
        for (T * r = p; r + 1 < m; ++r)
            if (cmp(*(r + 1), *r))
                std::swap(*r, *(r + 1));
}

template <typename T>
bool less (T a, T b) { return a < b; }

template <typename T>
bool greater (T a, T b) { return a > b; }


template <typename T>
void sort(T * p, T * q, bool asc = true) {
    sort(p, q, asc ? &less<T> : &greater<T>);   // обязательно передать тип <T>
}

template <typename T>
void print_array(T * p, T * q) {
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
    print_array(a, a + size);
    
    sort(a, a + size);
    std::cout << "Sorted array:\n";
    print_array(a, a + size);

    sort(a, a + size, false);
    std::cout << "Desc sorted array:\n";
    print_array(a, a + size);

    return 0;
}
