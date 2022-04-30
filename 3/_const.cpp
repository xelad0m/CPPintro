#include <iostream>
using namespace std;

int main() {
    int a = 10;

    /* указатель на константу */
    const char * cstr = "C-style string";       // строки С
    cout << cstr << endl;                       // C-style string
    cout << *cstr << endl;                      // C
    cout << *(cstr + 2) << endl;                // s
    // *(cstr + 1) = '!';                       // assignment of read-only location ‘*(cstr + 1)’

    const  int * p1 = &a;
    int  const * p2 = &a;
    // *p1 = 20;             // assignment of read-only location ‘* p1’
    p2   = 0;             // ОК

       
    /* константный указатель */
    char str[] = { 'M','u','t','a','b','l','e',' ','s','t','r','i','n','g' };
    char ch = '!';
    char * const const_str = &ch;  

    int * const p3 = &a;    // константный указатель
    *p3 = 30;               // OK
    cout << *(p3 + 1) << endl;  // тоже ОК, хоть и указывает в данном случае куда попало

    char & l = str[0];          
    cout << *(&l + 3) << endl;  // ОК

    char * const pchar = str;
    cout << *(pchar + 3) << endl;


    // p3   = 0;               // assignment of read-only variable ‘p3’
    
    // константный указатель на константу


    int  const * const p4 = &a;

    char const * const const_pchar = cstr;
    cout << *(const_pchar + 3) << endl;

    // *p4 = 30;           // assignment of read-only location ‘*(const int*)p4’
    // p4   = 0;           // assignment of read-only variable ‘p4’


    // Объявите переменную c именем m, в которой хранится указатель на двумерный массив 
    // целых чисел (int), выделенный в динамической памяти, так чтобы 
    // содержимое массива нельзя было поменять, т. е. компилятор должен выдавать ошибку при
    // попытке произвести над m любое действие, которое изменит значение m[i][j] для любых i и j.

    int **m;

    int m1[] = {1,2};
    int m2[] = {3,4};
    
    int * m0[] = {m1, m2};

    m = m0;
    m[1][0] = 5;
    cout << m[1][0] << endl;

    int const * const * M;
    M = m;
    cout << M[1][0] << endl;
    // M[1][0] = 10;
    // M[0] = m2;
    cout << M[0][0] << endl;




    return 0;
}