#include <iostream>   
using namespace std;                

union tag_value     // хранит в один момент времени только одну из переменных (нужно для экономии памяти)
{
    int vi;
    double vd;
    char vc;
};

struct tag_var
{
    union tag_value value;
    short type_var; // 0 - vi, 1 - vd, 2 - vs
};

int main() 
{   
    struct tag_var var[3];
    
    var[0].type_var = 0;
    var[0].value.vi = 10;

    var[1].type_var = 1;
    var[1].value.vd = 2.3;

    var[2].type_var = 2;
    var[2].value.vc = 'd';

    for (int i = 0; i < 3; i++)
    {
        switch (var[i].type_var)
        {
        case 0: cout << "1: " << var[i].value.vi << endl; break;
        case 1: cout << "2: " << var[i].value.vd << endl; break;
        case 2: cout << "3: " << var[i].value.vc << endl; break;
        default: cout << "Not defined" << endl; break;
        }
    }

    return 0;
}