#include <iostream>

#include <iomanip>      // fixed, setprecision
#include <cmath>        // trunc, floor, ceil, round

using namespace std;

// Дан многочлен P(x)=anxn + an−1xn−1+ … + a1x + a0 и число x. Вычислите значение этого многочлена, воспользовавшись схемой Горнера:
// P(x)=(…(((anx + an−1)x + an−2)x + an−3) … )x+ a0
double gorner()
{
    int n;
    double x, ai, a0;
    cin >> n >> x >> a0;
    while(n--)
    {
        cin >> ai;
        a0 = a0 * x + ai;
    }
    return a0;
}

void slau2x2() {
    /*ax+by=e cx+dy=f
    return case x0 y0 || k(x|y) + n */
    double a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    double det = a * d - b * c;
    double dx = e * d - b * f;
    double dy = a * f - c * e;
    
    if (det != 0) {
        cout << 2 << " " << (e * d - b * f) / (a * d - b * c ) << " " << (a * f - e * c) / (a * d - b * c );
    } else if ( dx != 0 || dy != 0 ) {
        cout << 0;
    } else if ( a==0&&b==0&&c==0&&d==0 ) {
        if (e!=0 || f!=0) 
            cout << 0;
        else 
            cout << 5;
    } else if (a==0 && c==0) {
        if (b != 0)
            cout << 4 << " " << e / b;
        else
            cout << 4 << " " << f / d;
    } else if (b == 0 && d == 0) {
        if (a != 0)
            cout << 3 << " " << e / a;
        else 
            cout << 3 << " " << f / c;
    } else if (b != 0) {
        cout << 1 << " " << -a / b << " " << e / b;
    } else {
        cout << 1 << " " << -c / d << " " << f / d;
    }
}


int main() {
    
    double pi = atan(1) * 4;                // уот так уот

    cout << fixed << setprecision(3);       // уот так уот
    cout << pi * 0.5 * 0.5 << '\n';

    double x = 5.6, y = -3.6;

    cout << trunc(x) << " " << trunc(y) << "\n";
    cout << floor(x) << " " << floor(y) << "\n";
    cout << ceil(x) << " " << ceil(y) << "\n";
    cout << round(x) << " " << round(y) << "\n";

    return 0;
}