/*
https://habr.com/ru/post/654741/
Аналоги new delete для C через макросы

Самый очевидный недостаток - нет никаких проверок на то что было передано в первый 
и второй аргумент, а значит и гарантии на то что всё правильно сработает.
*/

#include <stdio.h>

#include <malloc.h>
#define new(t,...) calloc(#__VA_ARGS__[0]!='\0'?__VA_ARGS__:1,sizeof(t))
#define delete(arg) free(arg)

int main(void)
{
int array[5] = {1, 2, 3, 4, 5};
int *u = array+sizeof(int);
printf("%d", *u); /* ожидание: 2. реальность: 5. */


// используем макрос для аналогa new из CPP (скобки нужны для )
int i = 42;
int *a = new(int);          //выделилась память под одну ячейку типа int
// int *b = new(int, 5);      //выделилась память под 5 ячеек типа int

*a = i;
printf("%d", *a);

return 0;
}
