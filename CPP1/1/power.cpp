#include <iostream>

using namespace std;

int power(int x, unsigned p) {
    int answer = x;
    if (p == 0) {
        return 1;
    } else if (x == 0) {
        return 0;
    } else
        for (int i = 1; i < p; i++)
            answer *= x;
            
    return answer;
}

int main() {
    int x = 0;
    unsigned p = 0;

    while (true) {
        cout << "Enter x and p: \n";
        cin >> x >> p;
        cout << "x ** p = " << power(x, p) << "\n";
    }

    return 0;
}