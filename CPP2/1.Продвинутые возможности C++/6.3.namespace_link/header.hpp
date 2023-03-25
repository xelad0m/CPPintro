#include <string>

namespace 
{
    struct Test 
    { 
        std::string data; 
    };

    inline void foo() { }

    static void bar() { }

    void foobar() { }
}

void file1();
void file2();
void file3();