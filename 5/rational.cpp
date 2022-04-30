/* Вам дан класс Rational, который описывает рациональное число. В нем определены 
методы add, sub, mul и div, которые прибавляют к нему число, отнимают число, умножают на 
число и делят на число соответственно. Кроме того в нем определен метод neg, 
который меняет знак на противоположный.

Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли 
принимать в качестве аргументов и объекты типа Rational и целые числа. Кроме того вам 
необходимо определить операторы унарного минуса и плюса для класса Rational.

Требования к реализации: ваш код не должен вводить или вводить что-либо, 
реализовывать функцию main не нужно. Кроме того, нельзя (это совершенно не нужно) 
использовать динамическую память или подключать какие-либо библиотеки.
*/

/* Добавьте в класс Rational оператор приведения к double. Все операторы из предыдущих 
заданий отсутствуют и реализовывать их не нужно. Метод to_double можно использовать 
в этом задании. */


#include <iostream>

struct Rational {
    Rational(int numerator = 0, int denominator = 1)            // explicit запретил бы приведение int -> Rational, а так все ОК
    : numerator_(numerator), denominator_(denominator) 
    {}

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    double to_double() const {
        return numerator_ / (double) denominator_;
    }

    operator double() const {                      // к типу double
        return this->to_double(); 
    }

    Rational & operator +=(Rational const& r2) {   // возврат по ссылке строго обязателен, иначе (x += 1) += 1 не будут возвращать то что планируется
        add(r2);                                   // а возвращать промежуточное значение из первых скобок. Остальные улетят со стека в никуда.
        return *this;                              
    }

    Rational & operator -=(Rational  const& r2) {
        sub(r2);
        return *this;
    }

    Rational & operator *=(Rational  const& r2) {
        mul(r2);
        return *this;
    }

    Rational & operator /=(Rational  const& r2) {
        div(r2);
        return *this;
    }

    // унарные + и - только методами класса (кроме того const, т.к. не должны менять this)
    Rational operator -()  const { 
        return  Rational(-numerator_, denominator_);
    } 

    Rational operator +()  const { 
        return  Rational(+numerator_, +denominator_); 
    } 

    // int get_numerator() const { return this->numerator_; }
    // int get_denominator() const { return this->denominator_; }

    /* вместо геттеров можно использовать ключ friend: делает функцию членом класса (но без 
        без указателя this), которая как и любой метод получает доступ к приватным полям */
    friend bool operator==(Rational const& a, Rational const &b){
        double A = a.numerator_ / (double) a.denominator_; 
        double B = b.numerator_ / (double) b.denominator_; 
        return A == B;
    }

    friend bool operator<(Rational const& a, Rational const& b) {
            double A = a.numerator_ / (double) a.denominator_; 
            double B = b.numerator_ / (double) b.denominator_; 
        return A < B;
    }

private:
    int numerator_;
    int denominator_;
};

Rational operator + (Rational r1, Rational const& r2) { return  r1 += r2; }
Rational operator - (Rational r1, Rational const& r2) { return  r1 -= r2; }
Rational operator * (Rational r1, Rational const& r2) { return  r1 *= r2; }
Rational operator / (Rational r1, Rational const& r2) { return  r1 /= r2; }

/* Don't use to_double method: задача - получить доступ к приватным полям объектов
   this нету, в класс совать нет смысла. Нужен геттер в классе */
// bool  operator ==(Rational  const& a, Rational  const& b) {
//     double A = a.get_numerator() / (double) a.get_denominator(); 
//     double B = b.get_numerator() / (double) b.get_denominator(); 
//     return A == B; 
// }

// bool  operator < (Rational  const& a, Rational  const& b) { 
//     double A = a.get_numerator() / (double) a.get_denominator(); 
//     double B = b.get_numerator() / (double) b.get_denominator(); 
//     return A < B; 
// }

bool  operator !=(Rational  const& a, Rational  const& b) { return !(a == b); }
bool  operator > (Rational  const& a, Rational  const& b) { return b < a; }
bool  operator <=(Rational  const& a, Rational  const& b) { return !(b < a); }
bool  operator >=(Rational  const& a, Rational  const& b) { return !(a < b); }

int main() {

    Rational r1(1, 2);
    Rational r2(1, 2);
    (r1 += r2) += r2;
    std::cout << r1.to_double() << std::endl;   // 1.5

    Rational a(0);                              // иниц. 0 -> a=0/1
    ((a += 5) += 5) +=5;                        
    std::cout << a.to_double() << std::endl;    // 15

    std::cout << (a < r1) << std::endl;
    std::cout << (r1 >= r2) << std::endl;

    std::cout << (double) r2 << std::endl;

    return 0;
}