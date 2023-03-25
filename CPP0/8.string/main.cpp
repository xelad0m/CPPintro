#include <iostream>
#include <algorithm> // count
#include <string>    // string
#include <cmath>

using namespace std;

bool is_digit(char c) {
    return (c <= '9' && c >='0');
}

char upper(char c) {
    if (c >= 'a' && c <= 'z')
        return c + 'A' - 'a';
    return c;
}

char reverse(char c) {
    if (c >= 'a' && c <= 'z') 
        return c + 'A' - 'a';
    else if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    return c;
}

int wcount(const string s) {
    return std::count(s.begin(), s.end(), ' ');
}


bool is_palindrome(string s) {
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] != s[n - i - 1])
            return false;
    }
    return true;
}

string max_word(string s) {
    int cnt = 0, len = 0, pos = 0, n = s.size();

    for (int i = 0; i < n; ++i) {
        if (s[i] == ' ' || i == n - 1) {
            if (i == n - 1 && s[i] != ' ') {    // последний символ
                ++i;
                ++cnt;
            }
            if (len < cnt) {
                len = cnt;
                pos = i - len;
            }
            cnt = 0;
        } else { 
            ++cnt;
        }
    }

    return s.substr(pos, len);
}

int my_stoi(string s) {
    int n = s.size();
    int res = 0;
    static int pow10[3] = {1, 10, 100}; // quickest pow 

    for (int i = n - 1; i >= 0; --i) {
        if (s[i] >= '0' && s[i] <= '9') {
            res += (s[i] - '0') * pow(10,  n - i - 1);
        } else {
            throw std::invalid_argument( "other than [0-9] symbols in string" );
        }  
    }
    return res;
}

bool is_ip(string s) {
    int parts = 0, cnt = 0, len = 0, pos = 0;
    int n = s.size();
    string part;
    int num;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '.' || i == n - 1) {
            if (i == n - 1 && s[i] == '.') return false;    // на точку заканчиваться не может
            if (i == n - 1 && s[i] != '.') {                // последний символ
                ++i;
                ++cnt;
            }
            len = cnt;
            pos = i - len;
            cnt = 0;
            part = s.substr(pos, len);
            try {
                num = my_stoi(part);
            } catch ( std::invalid_argument const& ex ) {
                return false;
            }
            if (num < 0 || num > 255 || len == 0) {
                return false;
            }
            ++parts;
        } else { 
            ++cnt;
        }
    }

    return parts == 4;
}


int main() {

    cout << wcount("In the town where I was born") << endl;

    cout << (is_palindrome("kayak") ? "yes" : "no") << endl;
    
    cout << max_word("Everyone 1veryone of us has all we needneedneed") << endl;

    cout << (is_ip("127.0.0.44") ? "yes" : "no") << endl;

    return 0;
}
