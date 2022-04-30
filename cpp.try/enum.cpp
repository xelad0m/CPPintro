#include <iostream>   
using namespace std;                

union tag_value     // хранит в один момент времени только одну из переменных (нужно для экономии памяти)
{
    int vi;
    double vd;
    char vc;
};

enum tag_type {VT_NONE, VT_INT, VT_FLOAT, VT_CHAR};     // просто присваивает именам значения 0,1,2 ...

// enum color {red, green, blue};                          // другой пример
// enum color_type {clr_red, clr_green, clr_blue};         // так у них будут теже значения 0,1,2,3 и при сравнении будет (red==clr_red)
// enum color_type {clr_red=10, clr_green, clr_blue};      // чтобы этого избежать: так у них будут теже значения 10,11,12,13


struct tag_var
{
    union tag_value value;
    tag_type type_var;
};

int main() 
{   
    struct tag_var var[3];
    
    var[0].type_var = VT_INT;
    var[0].value.vi = 10;

    var[1].type_var = VT_FLOAT;
    var[1].value.vd = 2.3;

    var[2].type_var = VT_CHAR;
    var[2].value.vc = 'd';

    for (int i = 0; i < 3; i++)
    {
        switch (var[i].type_var)
        {
        case VT_INT: cout << "1: " << var[i].value.vi << endl; break;
        case VT_FLOAT: cout << "2: " << var[i].value.vd << endl; break;
        case VT_CHAR: cout << "3: " << var[i].value.vc << endl; break;
        default: cout << "Not defined" << endl; break;
        }
    }

    return 0;
}