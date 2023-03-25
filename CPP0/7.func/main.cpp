#include <iostream>
#include  <vector>
#include <string>   // string
#include <sstream>  // istringstream
#include <utility>  // pair
#include <iomanip>  // setw
#include <cmath>

using namespace std;

int min(int a, int b) {
    return (a < b ? a : b);
}

int min4(int a, int b, int c, int d) {
    return min( min (a, b), min(c, d) );
}

double distance(double a, double b, double c, double d) {
    return sqrt(pow(a-c, 2) + pow(b-d, 2));
}

double power(double a, int n) {
    if (n == 0) {
        return 1;
    } else if (n < 0) {
        return (1 / a) * power(a, n + 1);
    } 
    return a * power(a, n - 1);
}

double MinDivisor(int n) {
    for (int i, isqrt=sqrt(n); i <= isqrt; ++i) {    // sqrt() 1 time
        if (n % i == 0) 
            return i;
    }
    return n;
}

bool IsPrime(int n) {
    for (int i=2, isqrt=sqrt(n); i <= isqrt; ++i) {
        if (n % i == 0) 
            return false;
    }
    return true;
}

double power_fast(double a, int n) {    // n > 0
    if (n == 0)
        return 1;
    else if (n % 2) 
        return a * power(a, n - 1);
    else 
        return power(a * a, n / 2);
}

int fib(int n) {
    return (n < 2) ? n : fib(n - 1) + fib(n - 2);
}

// В небоскребе n этажей. Известно, что если уронить стеклянный шарик с этажа номер p, и шарик разобьется, то если уронить
// шарик с этажа номер p+1, то он тоже разобьется. Также известно, что при броске с последнего этажа шарик всегда разбивается.
// Вы хотите определить минимальный номер этажа, при падении с которого шарик разбивается. Для проведения экспериментов у вас 
// есть два шарика. Вы можете разбить их все, но в результате вы должны абсолютно точно определить этот номер.
// Определите, какого числа бросков достаточно, чтобы заведомо решить эту задачу.
int balls(int n) {
    // 0, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5 и т.д.
    if (n < 2) return 1;
    int cnt = 0, curr = 1;
    for (int i = 1; i < n; ++i) {
        if (cnt == curr) {
            cnt = 1;
            ++curr;
        } else {
            ++cnt;
        }
    }
   
    return curr;
}

// Дано число N. Определите, сколькими способами можно расставить на доске N×N N ферзей, не бьющих друг друга.
typedef vector<pair<int, int>> Queens;

bool two_queens(int& x1, int& y1, int& x2, int& y2) {
    // бьются ли 2 ферзя
    return ( ((x1 - x2) * (x1 - x2) == (y1 - y2) * (y1 - y2)) || x1 == x2 || y1 == y2 );
}

bool checked(int& x, int& y, Queens& queens) {
    // бьется ли ферзь с кем-то из списка ферзей на поле nxn
    if (queens.size() == 0) return false;

    for (auto q : queens)
        if (two_queens(x, y, q.first, q.second))
            return true;
    return false;
}

void put_queen(int col, int& n, int& counter, Queens& queens) {
    // пробуем поставить ферзя в колонку col, если это уже за пределами 
    // поля nxn, увеличиваем счетчик вариантов

    if (col == n) 
        ++counter;
    else {
        for (int row = 0; row < n; ++row) {
            if (!checked(row, col, queens)) {
                queens.push_back(pair<int,int>(row, col));
                put_queen(col + 1, n, counter, queens);
                queens.pop_back();
            }
        }
    }
}

int count_queens(int n) {
    int counter = 0;
    Queens queens(0);
    put_queen(0, n, counter, queens);

    return counter;
}


int main() {
    cout << min4(6,3,7,4) << endl;
    cout << distance(0,0,1,1) << endl;
    cout << power(2,-2) << endl;
    cout << fixed << setprecision(0) << MinDivisor(5) << endl;
    cout << IsPrime(17) << endl;
    cout << power_fast(3,2) << endl;
    cout << fib(8) << endl; // 21
    
    cout << endl;
    int n = 8;
    cout << "Queens:" << n << "x" << n << endl;
    cout << count_queens(n) << endl;
    return 0;
}
