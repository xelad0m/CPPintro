#include "pch.h"                    

#include <iostream>  
#include <cstring>         
using namespace std;                

int main() 
{   
    char ch;
    ch = 'a';
    ch = '"';
    cout << ch << endl;

    char str_1[100] = {'H', 'e', 'l', 'l', 'o', '\0'};      // C style, \0 - end
    cout << str_1 << endl;

    char str_2[100] = "Hello!";
    cout << str_2 << endl;

    char str_3[] = "Hello world!";
    cout << str_3 << endl;

    // strcpy, strcat
    char a[100];
    // a = "Hi!";                                           // низзя
    strcpy(a, "Hi!");                                       // copy
    strcat(a, "World!");                                    // concat
    cout << a << endl;

    int N = strlen(a);                                      // len
    cout << N << endl;

    // fgets, puts
    char b[100], c[20];
    // cin >> c;                                               // cin ВВОД ДО ПРОБЕЛА
    // gets(c);                                                // gets was deprecated in C++11 and removed from C++14. If you are using GCC6.0 or newer then by default it uses C++14 and won't be available.
    fgets(c, sizeof(c), stdin);                             // пришло на замену gets()
    c[strcspn(c, "\n")] = '\0';                             // заменить \n на \0
    
    strcpy(b, "Hello World");
    // int cmp = strcmp(b, c);
    if (strcmp(b, c) == 0) cout << "Equal strings:\n";
    else cout << "Not equal strings:\n";

    puts(b);                                                // вывод в stdou
    puts(c);

    // sprintf - пишет в переменную
    short age = 27;
    double weight = 87.5;
    char name[100] = "John";
    char str[200];
    sprintf(str, "Hello, %s! Your age is %d, wieght is %.2f", name, age, weight);     
    cout << str << endl;

    // atoi, atof
    char str_i[] = "120";
    char str_f[] = "120.54";
    int i = atoi(str_i);
    float f = atof(str_f);
    cout << i << " " << f << endl;

    return 0;
}