#include <iostream>   
using namespace std;                

typedef struct 
{
    char a;
    int b;
} VAR;

int main() 
{   
    VAR v = {'#', 5};
    VAR *p = &v;

    cout << (*p).a << " " << (*p).b << endl;

    p -> a = '*';     // присвоение полю структуры по указателю  
    p -> b = -8;      // с оператором ->

    (*p).a = '*';     // 
    (*p).b = -8;

    cout << (*p).a << " " << (*p).b << endl;

    return 0;
}