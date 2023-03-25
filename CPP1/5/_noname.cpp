#include <iostream>
using namespace std;

void foo(int&)
{
    // обратиться к аргументу низзя
    // но передать обязательно
}

void bar(int * p)
{
    p = new int (123);
    // *p += 1;
}

int main()
{   
    int i = 10;
    // foo();      // низзя
    foo(i);

    int * pi;
    *pi = 10;
    bar(pi);
    cout << *pi << endl;

    return 0;
}