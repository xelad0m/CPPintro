#include <iostream>
#include <algorithm> // count transform
#include <string>    // string
#include <sstream>  // istringstream
#include <cmath>
#include <set>
#include <map>
#include <vector>

using namespace std;

void examples() {
    // set
    set <int> s = {1, 2, 3};
    s.insert(42);
    cout << (s.find(42) == s.end() ? "not found\n":"found\n");
    s.erase(42);
    
    for (auto now = s.begin(); now != s.end(); ++now)
        cout << *now << " ";
    cout << endl;
    
    // multiset - можно использовать для сортировки или подсчета (там внутре дерево)
    multiset <int> ms = {3, 2, 1, 2, 3, 1, 2, 3, 4, 2,1};
    for (auto now = ms.begin(); now != ms.end(); ++now)
        cout << *now << " ";
    cout << endl;

    cout << "n: " << ms.size() << endl;

    int count = 0;
    for (auto now = ms.lower_bound(1); now != ms.upper_bound(1); ++now)
        ++count;
    cout << "1: " << count << endl;
    
    // пересечение уот так уот
    vector <int> intersect;
    set_intersection(s.begin(), s.end(), ms.begin(), ms.end(), back_inserter(intersect));
    for (auto i : intersect)
        cout << i << " ";
    cout <<endl;
    // map - ключи, как и в сете, будут упорядочены
    map <int, string> m;
    m[112] = "sos";
    m[903] = "beeline";

    if (m.find(112) != m.end())
        cout << "found\n";

    for (auto now : m) 
        cout << now.first << "->" << now.second << endl;
    cout << endl;
}


void synonim(string input) {
    std::istringstream ccin(input);

    map <string, string> syn;
    
    int n;
    string a, b;
    ccin >> n;

    for (int i = 0; i < n; ++i) {
        ccin >> a >> b;
        syn[a] = b;
        syn[b] = a;
    }
    ccin >> a;
    cout << syn[a] << endl;
}

// lat-eng
void tokenize (string & str, string delim, vector<string> &out){
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != string::npos){    
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}


void latin(string input) {
    std::istringstream ccin(input);

    map <string, set<string>> vocab;
    
    int n;
    string s;
    ccin >> n >> ws; // ws пройти \n от cin
    
    for (int i = 0; i < n; ++i) {
        vector<string> eng_lat;
        vector<string> lats;
        getline(ccin, s);
        tokenize(s, " - ", eng_lat);
        tokenize(eng_lat[1], ", ", lats);

        for (auto lat : lats)
            vocab[lat].insert(eng_lat[0]);
    }

    // хитрованский формат вывода
    cout << vocab.size() << endl;
    for (auto eng : vocab) {
        cout << eng.first << " - ";
        int sep = 0;
        for (auto lat : eng.second) {
            if (sep != eng.second.size() - 1) 
                cout << lat << ", ";
            else
                cout << lat << endl;
            ++sep;
        }
    }
}

int diff(const string& str1, const string& str2) {
    size_t size1 = str1.size();
    size_t size2 = str2.size();

    int differ = 0;
    for (size_t i = 0; i <= size1; i++) {
        if (str1[i] != str2[i])
            ++differ;
    }
    return differ;
}

// map словарь ударений
void breaks(string input) {
    std::istringstream ccin(input);

    map <string, set<string>> vocab;
    
    int n;
    string s;
    ccin >> n >> ws; // ws пройти \n от cin
    
    string str, key;
    for (int i = 0; i < n; ++i) {
        getline(ccin, str);
        key = str;
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });   
        vocab[key].insert(str);
    }
    
    getline(ccin, str);
    vector<string> tokens;
    tokenize(str, " ", tokens);

    int errors = 0;
    for (auto t : tokens) {
        key = t;
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });
        if (diff(key, t) != 1) {
            ++errors;   // нет ударения или не одно ударение
        } else if (vocab.find(key) != vocab.end() && vocab[key].find(t) == vocab[key].end() )  {
            ++errors;   // в словере нет такого варианта ударения
        }

        cout << key << ":" << t << ":" << diff(key, t) << endl;
    }
    cout << errors << endl;
}


int main() {
    examples();
    
    string in = "3\nHello Hi\nBye Goodbye\nList Array\nGoodbye";
    synonim(in);

    in = "3\napple - malum, pomum, popula\nfruit - baca, bacca, popum\npunishment - malum, multa";
    latin(in);

    in = "4\ncAnnot\ncannOt\nfOund\npAge\nThe PAGE cannot be found";
    breaks(in);

    return 0;
}

