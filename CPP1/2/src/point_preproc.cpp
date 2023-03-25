# 1 "point.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "point.cpp"
# 1 "point.hpp" 1
       

struct Point
{

    double x;
    double y;

    void shift(double x, double y);
};
# 2 "point.cpp" 2

void Point::shift(double x, double y)
{
    this->x += x;
    this->y += y;
}
