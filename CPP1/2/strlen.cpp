// Очень часто для работы со строками нам нужно сначала вычислить длину строки. 
// Для C-style строк длина нигде явно не хранится, но её можно вычислить. 
// Напишите функцию, которая вычисляет длину C-style строки. Учтите, что завершающий 
// нулевой символ считать не нужно. 

#include <iostream>
using namespace std;


unsigned strlen(const char *str)
{   
    int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

int main() 
{  
    const char *s = "C-style string";
    cout << "strlen = " << strlen(s) << endl;

    return 0;
}