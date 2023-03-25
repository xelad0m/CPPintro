#include <iostream>
#include <string>
using namespace std;

struct  Person {
    Person(string  const& name, int age) 
    : name_(name), age_(age)
    { }

    virtual ~Person() { }

    virtual string name() const { return  name_ ; }

    virtual string occupation() const = 0;

private:
    string name_;
    int age_;
};

struct  Teacher : Person {
    Teacher(string  const& nm, int age, string  const& course)      // nm - чтобы не перекрывалось с name()
    : Person(nm, age), course_(course) 
    { 
        std::cout  << name() << std::endl; // 
    }   

    virtual string occupation() const { return  "teacher"; }

    virtual string course() const { return  course_ ; }

private:
    string course_;    
};

struct  Professor : Teacher {
    Professor(string  const& name, int age, string  const& course,  // тут нет вызова name() в определении, поэтому похер
              string const& thesis)                             
    : Teacher(name, age, course), thesis_(thesis)
    {}

    virtual string thesis() const { return thesis_; }                        

    virtual string name() const { return "Prof. " + Person::name(); }  

    virtual string occupation() const { return  "professor"; }

private:
    string thesis_;
};


int main()
{
    Professor p("Stroustrup", 63, "C++", "The C++ language"); 
    return 0;
}