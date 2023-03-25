#include <iostream>
using namespace std;

// универсальная функция для возведения в квадрат 

// через полиморфную похабщину
struct  INumber {
    virtual ~INumber() {}
    virtual INumber * multiply(INumber * x) const = 0;
};

struct  Int : INumber { 
    int data_;
    Int(const int & i) : data_(i) { }
    INumber * multiply(INumber * x) const {
        return new Int(this->data_ * ((Int *)x)->data_); 
    }
};

struct  Float : INumber {
    float data_;
    Float(const float & f) : data_(f) { }
    INumber * multiply(INumber * x) const { 
        return new Float(this->data_ * ((Float *)x)->data_); }
};

INumber * square(INumber * x) { return x->multiply(x); }


// через шаблонную функцию
template <typename Num>
Num square(Num x) { return x * x; }     // для любого типа с оператором умножения


int main() 
{   
    // через полиморфную похабщину
    INumber * i = new Int(4);           // к указателю на базовый тип приводится само
    INumber * f = new Float(3.5);

    INumber * ii = new Int(5);
    INumber * ff = new Float(5.5);

    ii = ii->multiply(i);
    ff = ff->multiply(f);

    cout << ((Int*)ii)->data_ << endl;
    cout << ((Float*)ff)->data_ << endl;

    cout << ((Int*)square(ii))->data_ << endl;
    cout << ((Float*)square(ff))->data_ << endl;

    // через шаблонную функцию
    cout << square(15) << endl;
    cout << square(.3) << endl;
}