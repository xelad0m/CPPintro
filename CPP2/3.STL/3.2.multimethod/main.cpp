#include <iostream>

#include <map>          // map
#include <typeindex>    // type_index
#include <functional>   // function
#include <utility>      // pair


// базовый класс фигуры (полиморфный)
struct Shape {
    virtual ~Shape() {}
    virtual void dummy() {}
};

// прямоугольник
struct Rectangle : Shape {};

// треугольник
struct Triangle : Shape {};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b) {
    std::cout << "rectangles intersecton" << std::endl;
    return 0;
};

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b) {
    std::cout << "rectangle - triangle intersecton" << std::endl;
    return 0;
};

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result
    
    bool commutative = Commutative;
    std::map<std::pair<std::type_index, std::type_index>, 
             std::function<Result(Base*, Base*)>> methods;

    void addImpl(std::type_index t1, std::type_index t2, std::function<Result(Base*, Base*)> f   )
    {   
        // сохраняет в ключе словаря правильный порядок аргументов,
        // коммутативность не должна проверяться

        // typeid возвращает const std::type_info&, 
        // std::type_index его потомок, поэтому приводится неявно

        this->methods[{t1, t2}] = f;
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а 

        auto it = this->methods.find({typeid(*a), typeid(*b)});

        if ( it != this->methods.end() ) {
            std::cout << "[hasImpl]: " << typeid(*a).name() << ", "<< typeid(*b).name() << std::endl;
            return true;
        } else if (this->commutative) {
            it = this->methods.find({typeid(*b), typeid(*a)});
            if ( it != this->methods.end() ) {
                std::cout << "[hasImpl] rev.args: " << typeid(*b).name() << ", "<< typeid(*a).name() << std::endl;
                return true;
            }
        }

        return false; 
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        
        if (this->commutative) {
            
            auto it = this->methods.find({typeid(*a), typeid(*b)});

            if ( it != this->methods.end() ) {
                std::cout << "[call]: " << typeid(*a).name() << ", "<< typeid(*b).name() << std::endl;   

                return this->methods.at({typeid(*a), typeid(*b)})(a, b);
            } else {
                std::cout << "[call] rev.args: " << typeid(*b).name() << ", "<< typeid(*a).name() << std::endl;   

                return this->methods.at({typeid(*b), typeid(*a)})(b, a);
            }
        }

        return this->methods.at({typeid(*a), typeid(*b)})(a, b);
    }

};



int main()
{
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным 
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);
    std::cout << "Size: " << is_intersect.methods.size() << std::endl;

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);
    std::cout << "Size: " << is_intersect.methods.size() << std::endl;

    // создаём две фигуры    
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
        // вызывается функция is_intersect_r_t(s2, s1)
        bool res = is_intersect.call(s1, s2);
        
        // ... и наиборот
        res = is_intersect.call(s2, s1);
        std::cout << res << std::endl; // dummy use

        // Замечание: is_intersect_r_t ожидает,
        // что первым аргументом будет прямоугольник
        // а вторым треугольник, а здесь аргументы
        // передаются в обратном порядке. 
        // ваша реализация должна самостоятельно 
        // об этом позаботиться
    }

    return 0;
};
