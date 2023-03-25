#include <iostream>
#include  <vector>
#include <string>   // string
#include <sstream>  // istringstream

using namespace std;

// Известно, что на доске 8×8 можно расставить 8 ферзей так, 
// чтобы они не били друг друга. Вам дана расстановка 8 ферзей 
// на доске, определите, есть ли среди них пара бьющих друг друга.

bool two_queens(int x1, int y1, int x2, int y2) {
    return ( ((x1 - x2) * (x1 - x2) == (y1 - y2) * (y1 - y2)) || x1 == x2 || y1 == y2 );
}

bool queens(std::string input) {
    // прост перебором, не Гаусс
    std::istringstream ccin(input);

    vector <int> xs, ys;
    int n = 0, x, y;
    while (ccin >> x >> y) {
        xs.push_back(x);
        ys.push_back(y);
        ++n;
    }


    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (two_queens(xs[i], ys[i], xs[j], ys[j])) {
                return true;
            }
        }
    }

    return false;
}


// N кеглей выставили в один ряд, занумеровав их слева направо числами от 1 до N. 
// Затем по этому ряду бросили K шаров, при этом i-й шар сбил все кегли с номерами 
// от li до ri включительно. Определите, какие кегли остались стоять на месте.

void pins_left(std::string input) {
    std::istringstream ccin(input);

    int n, k;
    ccin >> n >> k;

    vector<bool> pins(n, true);         // size, default

    int x, y;
    while (ccin >> x >> y) {
        for (int i = x; i <= y; i++)    // 1-based x,y
            pins[i - 1] = false;
    }

    for (auto pin : pins)
        cout << (pin ? "I" : ".");
    
    cout << "\n";
}

int main() {
    std::string qs = "1 8\n2 7\n3 6\n4 5\n5 4\n6 3\n7 2\n8 1";
    std::string ps = "10 3\n8 10\n2 5\n3 6";

    cout << (queens(qs) ? "YES" : "NO" ) << endl;
    
    pins_left(ps);
    return 0;
}