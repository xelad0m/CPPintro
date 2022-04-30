#include <iostream>
using namespace std;

int foo(){
    cout << "Hello!" << endl;
    return 2;
}

int bar(){
    int * m[1];             // массив размера 1
    m[3] = (int *) &foo;    // обращаемся за его границы (который находится выше по стеку)
                            // и пишем туда адрес функции foo()
    return 1;
}

int  main( ){
    bar();                  // при выходе из bar() вызовется foo()
                            // Hello!
                            // Ошибка сегментирования (стек памяти сброшен на диск)
    return  0;
}