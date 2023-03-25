/*Реализуйте функцию array_size, которая возвращает размер массива, переданного в качестве 
параметра. Функция должна работать только для массивов! Т. е. если функции передать 
указатель, должна произойти ошибка компиляции. Примеры:

int ints[] = {1, 2, 3, 4};
int *iptr = ints;
double doubles[] = {3.14};
array_size(ints); // вернет 4
array_size(doubles); // вернет 1
array_size(iptr); // тут должна произойти ошибка компиляции

Hint: в одной из первых недель мы вам показывали трюк с передачей массивов только заданного 
размера в функцию (передача массива по ссылке), совместите его с вашими знаниями о шаблонах.
*/

#include <iostream>
#include <cstddef> // size_t

using namespace std;


template <class Type, size_t N>         // templ.arg.deduction -> второй параметр компилятору известен, 
                                        // он неявно присутствует в определении, его пропускают просто для удобства
size_t array_size(Type (&arr)[N])       // а тут массив Type передается по ссылке Type (&arr)[], а не массив ссылок Type & arr[]
{ return (size_t) ( sizeof(arr) / sizeof(Type) ); } // N - константа времени компиляции (в вызывающем коде м.б. неявная)

// + https://habr.com/ru/post/251091/
// а тут есть более тонкий момент оказывается. Ссылка на массив это не тоже самое что указатель на массив,
// хотя адрес одинаковый. Размер указателя был бы равен размеру Type, а размер ссылки равен размеру всего объекта
// Именно поэтому работает sizeof(arr) / sizeof(Type). О, как...
// Отсюда еще один интересный момент: 
// int b[2];
// int *c = b;     // всегда назывался указатель на массив (но размер то int)
// int (*a)[2];    // а вот так "настоящий" (хоть и бессмысленный, т.к. итерировать не получится без 
// приведения, а привести не получится если не знаем о типе) указатель на массив (размер N*sizeof(int))


int main()
{   
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    cout << array_size(ints) << endl;       // вернет 4
    cout << array_size(doubles) << endl;    // вернет 1
    // cout << array_size(iptr) << endl;       // ошибка компиляции

    return 0;
}