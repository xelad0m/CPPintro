#include <iostream>

using namespace std;

// сумма цифр
int digit_sum (int a) {
    int sum = 0;
    while (a != 0) {
        sum = sum + a % 10;
        a = a / 10;
    }
    return sum;
}

std::string is_lucky(int part1, int part2) {
    
    int sum1 = digit_sum(part1);
    int sum2 = digit_sum(part2);

    return (sum1 == sum2) ? "lucky" : "unlucky";

}

// По данному целому числу N распечатайте все квадраты натуральных чисел, не превосходящие N, в порядке возрастания.
void squares(int n) {
    int i = 1;
    while (i * i <= n) {
        std::cout << i * i << " "; 
        i++;
    }
    std::cout << "\n";
}

// Дано целое число, не меньшее 2. Выведите его наименьший натуральный делитель, отличный от 1.
void gd(int n) {
    int i = 1;
    while (n % ++i);
    std::cout << i << "\n"; 
}

// По данному числу N распечатайте все целые степени двойки, не превосходящие N, в порядке возрастания.
void pow2(int n) {
    int i = 1;
    while (i <= n) {
        std::cout << i << " "; 
        i *= 2;
    };
    std::cout << "\n"; 
}

// Дано натуральное число N. Выведите слово YES, если число N является точной степенью двойки, или слово NO в противном случае.
bool is_pow2(int n) {
    int i = 1;
    while (i != n) {
        i *= 2;
        if (i > n) {
            return false;
        }
    };
    return true;

    // or bitarded
    // return (n & n - 1);
}

// Программа получает на вход последовательность целых неотрицательных чисел, каждое число записано в отдельной строке. 
// Последовательность завершается числом 0, при считывании которого программа должна закончить свою работу и вывести количество 
// членов последовательности (не считая завершающего числа 0).
void counter() {
    int n, i = 0;
    while(std::cin >> n && n && ++i);
    std::cout << n;
}

// Определите сумму всех элементов последовательности, завершающейся числом 0.
void sum() {
   int sum = 0, n;
   while(std::cin >> n && (sum += n));
   std::cout << sum;
}

// Определите, какое количество элементов последовательности, равны ее наибольшему элементу.
void n_max() {
   int max = 0, max_counter = 1, n;
   while(std::cin >> n && n) {
       if (n > max) {
           max = n;
           max_counter = 1;
       } else if (n == max) {
           ++max_counter;
       }
   }
   std::cout << max_counter;
}

int fib_while(int n) {
    
    int f_nn = 0, f_n = 1, i = 2, f;
    if (n == 0) {
        return f_nn;
    } else if (n == 1) {
        return f_n;
    } else {
        while (i <= n) {
            f = f_n + f_nn;
            f_nn = f_n;
            f_n = f;
            ++i;
        }
    }

    return f;
}

int is_fib_while(int n) {
    
    int f_nn = 0, f_n = 1, i = 2, f;
    if (n == 0) {
        return f_nn;
    } else if (n == 1) {
        return f_n;
    } else {
        while (f <= n) {
            f = f_n + f_nn;
            if (f == n) {
                return i;
            }
            f_nn = f_n;
            f_n = f;
            ++i;
        }
    }

    return -1;
}


int main() {

    cout << is_lucky(123, 321) << endl;

    squares(50);
    gd(17);
    pow2(50);
    
    cout << ( is_pow2(1024) ? "YES" : "NO" ) << endl;
    cout << fib_while(9) << endl;

    cout << is_fib_while(fib_while(9)) << endl;

    return 0;
}