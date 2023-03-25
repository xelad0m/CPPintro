#include <iostream>   
using namespace std;                

typedef unsigned char BYTE;         // переопределение имени для типа

union tag_value
{
    int vi;
    double vd;
    char vc;
};

enum tag_type {VT_NONE, VT_INT, VT_FLOAT, VT_CHAR};

typedef struct tag_var              // задание имени для структур
{
    union tag_value value;
    tag_type type_var;
} VAR;

int main() 
{   
    BYTE ch;
    VAR var;    // понятность и читаемость

    return 0;
}