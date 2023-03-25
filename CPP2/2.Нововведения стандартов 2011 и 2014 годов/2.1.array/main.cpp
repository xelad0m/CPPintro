#include <iostream>
#include <cstddef>                      // size_t
#include "array.hpp"

typedef Array<int> Ints;

Ints move(Ints a) {
    Ints tmp = a;                       // к.копирования
    return std::move(tmp);              // к.перемещения (move)
    // return tmp;                      // не будет перемещения
}

int main()
{
    Ints a(Ints(5, 1));                 // ?? move (но его почему-то не происходит)
    Ints b(a);                          // copy
    Ints c(std::move(b));               // move
    a = b;                              // copy
    b = std::move(c);                   // move
    c = Ints(5, 1);                     // move
    Ints d = Ints(5, 1);                // ?? move (но его почему-то не происходит)

    return 0;
}