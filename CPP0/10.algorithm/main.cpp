#include <iostream>
#include <algorithm>    // sort count transform
#include <string>       // string
#include <sstream>      // istringstream
#include <utility>      // pair
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

struct man {
    int     height;
    string  name;
};

bool cmp(man a, man b) {
    return a.height < b.height;
}

void print(vector<int> v) {
    for (auto item: v) 
        cout << item << " ";
    cout << endl;
}

void examples() {
    // sort reverse
    vector<int> a { 5,3,7,3,2,5,8,7,4,5,2 };
    sort(a.begin(), a.end());
    print(a);
    reverse(a.begin(), a.end());
    print(a);

    // pair
    vector<pair<int, int>> b {{-1, -1},{-2, -2}};
    for (int i = 0, size = a.size(); i < size; ++i) {
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());
    for (auto item : b)
        cout << item.second << " ";                     // индексы
    cout << endl;
    
    // struct
    vector <man> c {{168, "Mary"},{165, "Kate"},{165, "Alice"},{175, "Bobby"},{180, "John"}};
    sort(c.begin(), c.end(), cmp); // func
    for (auto person : c)
        cout << person.name << "(" << person.height<< ") ";
    cout << endl;
    
    // stable_sort сохраняет взаимный порядок одинаковых элементов
    stable_sort(c.begin(), c.end(), [](man a, man b){ return a.height < b.height; }); // lambda
    for (auto person : c)
        cout << person.name << "(" << person.height<< ") ";
    cout << endl;

    // next_permutation 
    vector <int> d;
    for (int i = 0; i < 3; ++i) {
        d.push_back(i + 1);
    }
    while (next_permutation(d.begin(), d.end()))
        print(d);
}

// В обувном магазине продается обувь разного размера. Известно, что одну пару обуви можно надеть на другую, 
// если она хотя бы на три размера больше. В магазин пришел покупатель. Требуется определить, какое наибольшее 
// количество пар обуви сможет предложить ему продавец так, чтобы он смог надеть их все одновременно.
void shoes(string & input) {
    std::istringstream ccin(input);
    int size, n;
    ccin >> size >> n;
    vector<int> s(n);
    
    int i = 0;
    while (ccin >> n && ++i) {
        s[i] = n;
    }
    
    sort(s.begin(), s.end());
    
    int counter = 0;
    for (auto item: s) {
        if (item >= size) {
            ++counter;
            size = item + 3;
        }
    }
    
    cout << counter << endl;
}

// Во время проведения олимпиады каждый из участников получил свой идентификационный номер – 
// натуральное число. Необходимо отсортировать список участников олимпиады по количеству набранных ими баллов.

void osort(string & input) {
    std::istringstream ccin(input);
    int n;
    ccin >> n;

    vector<pair<int,int>> s;

    int id, score;
    while (ccin >> id && ccin >> score)
        s.push_back( {id, score} );

    sort(s.begin(), s.end(), [](pair<int,int> p1, pair<int,int> p2){ return p1.first < p2.first; });
    stable_sort(s.begin(), s.end(), [](pair<int,int> p1, pair<int,int> p2){ return p1.second > p2.second; });

    for (auto item : s)
        cout << item.first << " " << item.second << endl;
    cout << endl;
}

// Выведите все исходные точки в порядке возрастания их расстояний от начала координат.

struct Point {
    int x;
    int y;
};

bool dist0(Point& p1, Point& p2) {
    return sqrt(pow(p1.x, 2) + pow(p1.y,2)) < sqrt(pow(p2.x, 2) + pow(p2.y,2));
}

void sort_points(string & input) {
    std::istringstream ccin(input);

    int n, x, y;
    ccin >> n;

    vector <Point> ptx(n);

    while (ccin >> x >> y && n--) 
        ptx[n] = {x, y};
    
    sort(ptx.begin(), ptx.end(), dist0);

    for (auto pt : ptx)
        cout << pt.x << " " << pt.y << endl;
}

// Выведите фамилии и имена учащихся в порядке убывания их среднего балла.
struct Person {
    string name1, name2;
    int a, b, c;
};

bool avg_cmp(const Person & p1, const Person & p2 ) {
    return ((p1.a + p1.b + p1.c) / (float) 3) > ((p2.a + p2.b + p2.c) / (float) 3);
}

void names(string & input) {
    std::istringstream ccin(input);
    int n, i, a, b, c;
    string name1, name2;

    ccin >> n;

    vector <Person> px(n);
    
    i = n;  // если нам важен исходный порядок
    while (ccin >> name1 >> name2 >> a >> b >> c && n--) 
        px[i - n - 1] = {name1, name2, a, b, c};
    
    stable_sort(px.begin(), px.end(), avg_cmp);

    for (auto p : px)
        cout << p.name1 << " " << p.name2 << endl;

}


int main() {
    examples();

    cout << endl;
    string in = "26\n5\n30 35 40 41 42";
    shoes(in);
    
    cout << endl;
    in = "3\n101 80\n305 90\n200 14";
    osort(in);
    
    cout << endl;
    in = "2\n1 2\n2 3";
    sort_points(in);
    
    cout << endl;
    in = "3\nMarkov Valeriy 5 5 5\nSergey Petrov 1 1 1\nPetrov Petr 3 3 3";
    names(in);

    return 0;
}

