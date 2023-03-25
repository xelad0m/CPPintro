#include <iostream>

struct Unit; //опережающие объявление для последующих typedef-ов

//указатель на константное поле класса Unit
typedef const unsigned Unit::*c_Unit_ptr;      
//указатель константный метод класса Unit, без аргументов, возвращающий unsigned
typedef unsigned (Unit::*m_Unit_ptr)() const;  

struct Unit{
    
    Unit() : _id(0), _hp(0) {};                           //конструктор по умолчанию(пустой)
    Unit(unsigned id, unsigned hp) : _id(id), _hp(hp) {}; //конструктор от двух аргументов
    
    unsigned id() const { return _id; } //добавил реализацию метода
    static c_Unit_ptr return_HP() { return &Unit::_hp;}   
    //статический метод, возвращающий указатель на константное поле класса Unit
    
    private:            //сделал поля приватными
    const unsigned _id; //добавил константность
    const unsigned _hp; //указатель на поле класса Unit так просто уже не получить
};

//создание указателя на метод класса Unit
m_Unit_ptr method_ptr = &Unit::id; 
//создание указателя на статический метод класса Unit
c_Unit_ptr (*s_method)() = &Unit::return_HP;
//создание указателя на константное поле класса Unit,
//разыменование указателя на статический метод класса Unit,
//и его вызов без объекта, вне тела программы, 
//получая тем самым укатель на приватное поле класс Unit
c_Unit_ptr field_ptr  = (*s_method)(); 

//объявления указателей без typedef-ов
//unsigned (Unit::*method_ptr)() const = &Unit::id;
//не сработает с приватным полем класса
//const unsigned  Unit::*field_ptr = &Unit::_hp;


int main()
{
    //Инициализация объекта
    Unit u(15, 100);
    Unit * u_ptr = &u;
    
    //проверка работоспособности статического метода
    // c_Unit_ptr new_field_ptr  = Unit::return_HP(); 
    
    //вывод результатов работы указателей на экран
    std::cout<<(u.*method_ptr)()<<' '<<(u_ptr->*method_ptr)()<<'\n';
    std::cout<<u.*field_ptr<<' '<<(u_ptr->*field_ptr)<<'\n';
    
    return 0;
}