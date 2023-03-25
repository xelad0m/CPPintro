#include <iostream>

using namespace std;

// Даны три целых числа. Найдите наибольшее из них
int max(int a, int b, int c) {
    if (a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    
    return c;
}

// Даны три натуральных числа A, B, C. Определите, существует ли треугольник с такими сторонами. 
// Т.е. имеется ли число больше суммы других двух чисел
bool is_triangle(int a, int b, int c) {
    if (a >= b + c)
        return false;
    else if (b >= a + c)
        return false;
    else if (c >= a + b)
        return false;

    return true;
    // or
    // return b + c > a && a + c > b && a + b > c
}


// Даны три целых числа. Определите, сколько среди них совпадающих. Программа должна вывести 
// одно из чисел: 3 (если все совпадают), 2 (если два совпадает) или 0 (если все числа различны).
int is_equal(int a, int b, int c) {
    if ( a == b && b == c )
        return 3;
    else if ( a == b || a == c || b == c )
        return 2;
    
    return 0;
}

// Шахматная ладья ходит по горизонтали или вертикали. Даны две **различные** клетки шахматной доски, 
// определите, может ли ладья попасть с первой клетки на вторую одним ходом.
bool two_rooks(int x1, int y1, int x2, int y2)
{   
    if ( x1 == x2 || y1 == y2 )
        return true;
    
    return false;
}

// Шахматный король ходит по горизонтали, вертикали и диагонали, но только на 1 клетку. Даны две **различные** 
// клетки шахматной доски, определите, может ли король попасть с первой клетки на вторую одним ходом.
bool one_king(int x1, int y1, int x2, int y2)
{   
    if ( ( x1 - x2 >= -1 && x1 - x2 <= 1 ) && ( y1 - y2 >= -1 && y1 - y2 <= 1 ) )
        return true;
    
    return false;
    // or
    // return ((x1 - x2) * (x1 - x2) <= 1) || ((y1 - y2) * (y1 - y2) <= 1)
}

// Шахматный слон ходит по диагонали. Даны две **различные** клетки шахматной доски, определите, может 
// ли слон попасть с первой клетки на вторую одним ходом.
bool one_bishop(int x1, int y1, int x2, int y2)
{   
    if ( ( x1 - x2 == y1 - y2 ) || ( x1 - x2 == y2 - y1 ) ) 
        return true;
    
    return false;
    //
    // return ((x1 - x2) * (x1 - x2) == (y1 - y2) * (y1 - y2))
}

// Шахматный ферзь ходит по диагонали, горизонтали или вертикали. Даны две **различные** клетки шахматной доски, 
// определите, может ли ферзь попасть с первой клетки на вторую одним ходом.
bool one_queen(int x1, int y1, int x2, int y2)
{   
    if ( ((x1 - x2) * (x1 - x2) == (y1 - y2) * (y1 - y2)) || x1 == x2 || y1 == y2 )
        return true;
    
    return false;
}

// Шахматный конь ходит буквой “Г” — на две клетки по вертикали в любом направлении и на одну клетку по горизонтали, 
// или наоборот. Даны две **различные** клетки шахматной доски, определите, может ли конь попасть с первой клетки на вторую одним ходом.
bool one_knight(int x1, int y1, int x2, int y2)
{   
    int h2 = (x1 - x2) * (x1 - x2); // 1 || 4
    int v2 = (y1 - y2) * (y1 - y2); // 4 || 1
    if ( (h2 == 1 && v2 == 4) || (h2 == 4 && v2 == 1) )
        return true;
    
    return false;
    // or
    // return (((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) == 5)
}

// Шоколадка имеет вид прямоугольника, разделенного на N×M долек. Шоколадку можно один раз разломить по 
// прямой на две части. Определите, можно ли таким образом отломить от шоколадки ровно K долек.
bool rectangle(int n, int m, int k)
{   
    return ( ( k % n == 0 || k % m == 0) && k < n * m );
}

// Яша плавал в бассейне размером N×M метров и устал. В этот момент он обнаружил, что находится на расстоянии 
// X метров от одного из длинных бортиков (не обязательно от ближайшего) и Y метров от одного из коротких бортиков. 
// Какое минимальное расстояние должен проплыть Яша, чтобы выбраться из бассейна на бортик?
int jacob(int n, int m, int x, int y)
{
    int s = n < m ? n : m;
    int l = n > m ? n : m;

    x = x < s - x ? x : s - x;
    y = y < l - y ? y : l - y;
    return ( x < y ? x : y );
}


// Дано три числа. Упорядочите их в порядке неубывания
const char * sort3(int a, int b, int c) {
    int min = a < b ? ((a < c) ? a : c) : ((b < c) ? b : c);
    int max = a > b ? ((a > c) ? a : c) : ((b > c) ? b : c);
    int mid = a + b + c - min - max;

    char * str;
    sprintf(str, "%d %d %d", min, mid, max);
    return str;
}

// Есть две коробки, первая размером A1×B1×C1, вторая размером A2×B2×C2. Определите, можно ли разместить 
// одну из этих коробок внутри другой, при условии, что поворачивать коробки можно только на 90 градусов вокруг ребер.
std::string boxes(int a, int b, int c, int a1, int b1, int c1)
{   
    int min = a < b ? ((a < c) ? a : c) : ((b < c) ? b : c);
    int max = a > b ? ((a > c) ? a : c) : ((b > c) ? b : c);
    int mid = a + b + c - min - max;

    int min1 = a1 < b1 ? ((a1 < c1) ? a1 : c1) : ((b1 < c1) ? b1 : c1);
    int max1 = a1 > b1 ? ((a1 > c1) ? a1 : c1) : ((b1 > c1) ? b1 : c1);
    int mid1 = a1 + b1 + c1 - min1 - max1;

    if ( min == min1 && mid == mid1 && max == max1 )
        return "Boxes are equal";
    else if ( min <= min1 && mid <= mid1 && max <= max1 )
        return "The first box is smaller than the second one";
    else if ( min >= min1 && mid >= mid1 && max >= max1 )
        return "The first box is larger than the second one";

    return "Boxes are incomparable";
}

int main() {

    cout << max(1, 2, 3) << endl;
    cout << ( is_triangle(3, 5, 14) ? "YES" : "NO" ) << endl;
    cout << is_equal(2, 3, 3) << endl;

    cout << ( two_rooks(4, 4, 5, 5) ? "YES" : "NO" ) << endl;
    cout << ( one_king(4, 4, 5, 5) ? "YES" : "NO" ) << endl;
    cout << ( one_bishop(4, 4, 5, 5) ? "YES" : "NO" ) << endl;
    cout << ( one_queen(1, 1, 2, 2) ? "YES" : "NO" ) << endl;
    cout << ( one_knight(1, 1, 2, 3) ? "YES" : "NO" ) << endl;

    cout << ( rectangle(4, 2, 6) ? "YES" : "NO" ) << endl;

    cout << jacob(23, 52, 20, 43) << endl;
    
    cout << sort3(2, 3, 1) << endl;

    cout << boxes(2, 2, 3, 3, 2, 1) << endl;

    return 0;
}