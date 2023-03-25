#include <iostream>
#include  <vector>
#include <string>   // string
#include <sstream>  // istringstream
#include <utility>  // pair
#include <iomanip>  // setw

using namespace std;

// Дано нечетное число n, не превосходящее 15. 
// крч нарисовать звездочку из ./*
void star(int n) {
    vector<vector<char>> S(n, vector<char> (n, '.'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == n / 2 || j == n / 2 || i == j || i == n - j - 1) {
                S[i][j] = '*';
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << S[i][j] << " ";
        }
        cout << endl;
    }
}

void snake(int n, int m) {
    
    vector<vector<int>> S(n, vector<int> (m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i % 2 == 0) {
               S[i][j] = i * (m - 1) + i + j + 1;
            } else {
               S[i][m - j - 1] = i * (m - 1) + i + j + 1;
            }
            
        }
    }
        
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {        
            cout << setw(4) << S[i][j];
        }
        cout << endl;
    }
}


void diag(int n, int m) {
    
    vector<vector<int>> S(n, vector<int> (m));

    int cnt = 1;
    for (int k = 0; k < n + m - 1; ++k ) {  // количество диагонателей
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == k - j || j == k - i) {
                    S[i][j] = cnt++;
                }
            }
        }

    }
        
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {        
            cout << setw(4) << S[i][j];
        }
        cout << endl;
    }
}

void chess(int n, int m) {
    
    vector<vector<int>> S(n, vector<int> (m));

    int cnt = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ( (i + j) % 2 == 0) {
                S[i][j] = cnt++;
            }
        }
    }
        
    for (auto row : S) {
        for (auto val : row) {        
            cout << setw(4) << val;
        }
        cout << endl;
    }
}


void spiral(int n, int m) {
    // ru.stackoverflow.com
    vector<vector<int>> S(n, vector<int> (m));

    int Up = 0;    // Сужение сверху
    int Down = 0;  // Сужение снизу
    int Left = 0;  // Сужение слева
    int Right = 0; // Сужение справа

    // Переменные счетчики используемые в расчетах
    int k = 1; // Счетчик, который присваивает значение элементам массива
    int i = 0; // Координары строки
    int j = 0; // Координаты столбца

    while (k <= n * m)
    {
        S[i][j] = k;

        // Проверка возможности движения вправо
        if (i == Up && j < m - Right - 1)
            ++j; // производится движение по столбцу вправо

        // Проверка возможности движения вниз
        else if (j == m - Right - 1 && i < n - Down - 1)
            ++i; // производится движение по строкам вниз

        // Проверка возможности движения влево
        else if (i == n - Down - 1 && j > Left)
            --j; // производится движение по столбцу влево

        // Проверка возможности движения вверх
        else
            --i; // производится движение по строкам вверх

        // Сужение диапазона, если окружность заполнена
        if ((i == Up + 1) && (j == Left) && (Left != m - Right - 1))
        {
            ++Up;
            ++Down;
            ++Right;
            ++Left;
        }
        ++k; // Счетчик увеличен на 1
        // Цикл начинается заново
    }    
        
    for (auto row : S) {
        for (auto val : row) {        
            cout << setw(4) << val;
        }
        cout << endl;
    }
}

int main() {

    star(5);
    cout << endl;

    snake(5, 12);
    cout << endl;

    diag(3, 5);
    cout << endl;

    chess(3, 5);
    cout << endl;

    spiral(8, 7);
    cout << endl;

    return 0;
}