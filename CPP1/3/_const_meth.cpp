#include <iostream>
#include <string>
using namespace std;

struct Person {
    string name()  const {  // NB: const метод доступен, когда экземпляр константа 
        return name_;       // + const метод не может менять поля, т.к. this -> const
    }
    int age() const { 
        return age_; 
    }
// private:                 // с private не инициализируется
    string  name_;
    int  age_;
};

int main()
{
    Person pers { "Alex", 21 };

    cout << pers.name() << endl;

    return 0;
}