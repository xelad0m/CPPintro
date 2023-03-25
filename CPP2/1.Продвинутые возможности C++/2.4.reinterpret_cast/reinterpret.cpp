#include <iostream>
#include <string>

class Base {
public:
    double a;
    Base(double a_) : a(a_) {};

    friend std::ostream& operator << (std::ostream & out, Base const& sth);
};

class D1 : public virtual Base {
public:
    char D1_;
    D1(char d1, double ad) : Base(ad), D1_(d1)  {};

    friend std::ostream& operator << (std::ostream & out, D1 const& sth);
};

class D2 :public virtual Base {
public:
    std::string D2_;
    D2(std::string ds, double ad2) : Base(ad2), D2_(ds)  {};

    friend std::ostream& operator << (std::ostream & out, D2 const& sth);
};

class Whole : D1, D2 {
public:
    float wh_;
    Whole(double d1, char d1c, double d2, std::string d2s, float wh, double bs) : Base(bs), D1(d1c, d1), D2(d2s, d2), wh_(wh) {};
    friend std::ostream& operator << (std::ostream & out, Whole const& sth);
};


int main()
{
    Whole sth(0.2, 'a', 1.6, "hello there", 0.124, 123);
    std::cout << sth;
    std::cout << (D1 &) sth;
    std::cout << (Base&)(D1&)sth;
    // std::cout << static_cast<D2&>(sth); //error: ‘D2’ is an inaccessible base of ‘Whole’
    std::cout << (D2&)sth;
    std::cout << (Base&)(D2&)sth;

    
}

std::ostream& operator<<(std::ostream & out, Base const& sth)
{
    out << sth.a << ' ' << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream & out, D1 const& sth)
{
    out << sth.a << ' ' << sth.D1_ << ' ' << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream & out, D2 const& sth)
{
    out << sth.a << ' ' << sth.D2_ << ' ' << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream & out, Whole const& sth)
{
    out << sth.wh_  << ' ' << sth.D1_ << ' ' << ((D1&)sth).a << ' ' << sth.D2_ << ' ' << ((D2&)sth).a << std::endl;
    return out;
    
}