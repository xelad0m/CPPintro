// использование макросов вместо функций — это зло.
// Реализуйте макрос MAX от трёх параметров, который присваивает 
// целочисленной (int) переменной, переданной в качестве третьего аргумента, 
// наибольшее из значений, переданных в первых двух аргументах.

#include <iostream>

#define MAX(x, y, r) {int x_ = (x); int y_ = (y); int r_ = ((x_ > y_) ? x_ : y_); r = r_;}    /* присваивает r максимум из x и y */

using namespace std;

int main() {
    int a = 10;
    int b = 20;
    int c = 0;

    MAX(a, b, c);       // теперь c равно 20
    cout << c << endl;

    MAX(a += b, b, c);  // теперь a = с = 30
    cout << c << endl;

    int m = 0;
    MAX(++a, b, m);     // 31
    cout << m << endl;

    m = 0;
    MAX(b++, a, m);     // 31
    cout << m << endl;  

    m = 0;
    MAX(--a, b, m);
    cout << m << endl;

    m = 0;
    MAX(b, a--, m);
    cout << m << endl;

    m = 0;
    MAX(a - b, a + b, m);
    cout << m << endl;

    m = 0;
    MAX(a < b ? a : b, a < b ? b : a, m);
    cout << m << endl;


    return 0;
}