// Напишите функцию поиска первого вхождения шаблона в текст. В качестве первого параметра функция принимает 
// текст (C-style строка), в которой нужно искать шаблон. В качестве второго параметра строку-шаблон 
// (C-style строка), которую нужно найти. Функция возвращает позицию первого вхождения строки-шаблона, 
// если он присутствует в строке (помните, что в C++ принято считать с 0), и -1, если шаблона в тексте нет.

// Учтите, что пустой шаблон (строка длины 0) можно найти в любом месте текста. 

#include <iostream>
using namespace std;

struct test{
    int ret_value;
    const char *text;
    const char *pattern;
};

test tests[] = {
        {0, "", ""}, //0
        {0, "a", ""}, //1
        {0, "a", "a"}, //2
        {-1, "a", "b"}, //3
        {0, "aa", ""}, //4
        {0, "aa", "a"}, //5
        {0, "ab", "a"}, //6
        {1, "ba", "a"}, //7
        {-1, "bb", "a"}, //8
        {0, "aaa", ""}, //9
        {0, "aaa", "a"}, //10
        {1, "abc", "b"}, //11
        {2, "abc", "c"}, //12
        {-1, "abc", "d"}, //13
        {-1, "a", "aa"}, //14
        {-1, "a", "ba"}, //15
        {-1, "a", "ab"}, //16
        {-1, "a", "bb"}, //17
        {-1, "a", "aaa"}, //18
        {-1, "aa", "aaa"}, //19
        {0, "aaa", "aaa"}, //20
        {0, "aaab", "aaa"}, //21
        {1, "baaa", "aaa"}, //22
        {1, "baaaa", "aaa"}, //23
        {1, "baaab", "aaa"}, //24
        {-1, "abd", "abc"}, //25
        {2, "ababc", "abc"}, //26
        {3, "abdabc", "abc"}, //27
        {-1, "", "a"}, //28
        {2, "asasaf", "asaf"}, //29
        {2, "ababac", "abac"} //30
};

int check(const char *t, const char *p) 
{
    while ((*t++) && (*p++) && (*t == *p));

    if ((*t == '\0') && (*p == '\0'))
        return 1;
    if ((*t != '\0') && (*p == '\0'))
        return 1;
    if ((*t == '\0') && (*p != '\0'))
        return -1;
    return 0;
}

int strstr(const char *text, const char *pattern)
{
    int i = 0;
    int chk = 0;

    if (*pattern == '\0')
        return 0;
    if (*text == '\0')
        return -1;
    
    for ( ; *text ; ++text) {
        if (*text == *pattern) {
            chk = check(text, pattern);
            if (chk == 1) 
                return i;
            else if (chk == -1)
                return -1;          
        }
        i++;
    }
    return -1;
}



int main() 
{  
    const char *text = "ababac";
    const char *pattern = "abac";

    cout << strstr(text, pattern) << endl;

    cout << "Tests:" << endl;
    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        int ret = strstr(tests[i].text, tests[i].pattern);
        (tests[i].ret_value == ret) ? cout << "OK" : cout << "Failed";
        cout << " : " << i << " (" << tests[i].ret_value << " : " << ret << ")" << endl;
    }


    return 0;
}