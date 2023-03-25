// напишите рекурсивную функцию вычисления наибольшего общего делителя двух положительных целых чисел (Greatest Common Divisor, GCD). 
// Для этого воспользуйтесь следующими свойствами:
//     GCD(a,b)=GCD(b,a mod b) 
//     GCD(0,a)=a 
//     GCD(a,b)=GCD(b,a)
// Требования к реализации: в данном задании запрещено пользоваться циклами. Вы можете заводить любые вспомогательные функции, 
// если они вам нужны. Функцию main определять не нужно.

#include <iostream>
using namespace std;

unsigned gcd(unsigned a, unsigned b)
{
    // алгоритм Эквклида
    if (b > 0) {
        return gcd(b, a % b);
    }
    return a;
}

int main() 
{
    unsigned a = 0, b = 0;

    while (true) {
        cout << "Enter a and b (Ctrl+C to exit): \n";
        cin >> a >> b;
        cout << "GCD(a, b) = " << gcd(a, b) << endl;
    }
    return 0;
}
