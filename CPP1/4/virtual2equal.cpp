
/* (Задание повышенной сложности) Предполагаемое решение этого задания не переносимо с точки зрения стандарта, однако оно 
проверено на различных версиях компиляторов g++/clang++/msvc. Решение этого задания не обязательно для получения диплома 
по этому курсу, однако мы считаем его полезным, чтобы лучше понять как устроены виртуальные функции внутри.
Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает true, 
если оба указателя указывают на самом деле на объекты одного и того же класса, и false в противном случае (т.е. если оба 
указателя указывают на BinaryOperation, то возвращается true, а если один из них указывает на Number, а второй на BinaryOperation, 
то false).

Требования к реализации: пользоваться typeid и dynamic_cast запрещено. Вызывать методы по переданным указателям запрещено.
*/

#include <iostream>
using namespace std;

struct Expression
{
    virtual double evaluate() const = 0;                // абстрактный класс
    virtual ~Expression() { }                           // виртуальный, чтобы определить конкретного потомка в дин.памяти и вызвать его деструктор
};

struct Number : Expression
{
    Number(double value)                                // конструктов, а деструктора тут достаточно встроенного, в дин.памяти полей нет
        : value(value)                      
    {}
    
    double evaluate() const { return value; }           // однажды виртуальный - во всех наследниках тоже виртуальный

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }

    ~BinaryOperation ()         // деструктора по умолчанию недостаточно, т.к. поля ссылаются на дин.память (? пока не ясно)
    { 
        delete this->left;
        delete this->right;
    }

    double evaluate() const
    {
        switch (this->op) {
            case '+': return this->left->evaluate() + this->right->evaluate();
            case '-': return this->left->evaluate() - this->right->evaluate();
            case '*': return this->left->evaluate() * this->right->evaluate();
            case '/': return this->left->evaluate() / this->right->evaluate();
            default : throw;
        }
    }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

bool check_equals(Expression const *left, Expression const *right)
{
    void * lvptr = *(void **) left;     // преобразовать указатель на expr в общий указатель на указатель
    void * rvptr = *(void **) right;    // т.е. в указатель на место в памяти, где лежит указатель на vptr класса
    return ( lvptr == rvptr );          // почему он в начале, а не по смещению 16 как в дампе классов, пока не понятно
}

int main()
{
    // check
    Expression * expr1 = new BinaryOperation(new Number(4.5), '*', new Number(3));
    std::cout << expr1->evaluate() << std::endl;
    Expression * expr2 = new BinaryOperation(new Number(3), '+', expr1);
    std::cout << expr2->evaluate() << std::endl;
    Expression * expr3 = new Number(4.5);
    std::cout << expr3->evaluate() << std::endl;

    // должно быть что-то вроде: expr1 == expr2, expr1 != expr3

    // как предусмотренно выяснять тип в таких случаях
    std::cout << typeid(expr1).name() << " ";                   // даст P10Expression (т.е. ссылка на тип Expression)
    std::cout << typeid(*expr1).name() << std::endl;            // нужно разыменовать указатель, тогда даст 15BinaryOperation
    
    std::cout << typeid(expr3).name() << " ";             
    std::cout << typeid(*expr3).name() << std::endl;            // 6Number
    
    // кажись надо получить адреса vptr и если они равны, то это один тип, если нет, то разные
    // как это сделать? вот в чем вопрос.
    // типа он хранится самым первым, 64-битная машина, т.е. первые 8 байт экземпляра в памяти? получается, что так
    // хотя в дампе классов vptr=((& Expression::_ZTV10Expression) + 16) смещение +16

    void * vptr1 =  *(void**)expr1;     // преобразовать указатель на expr в общий указатель на указатель 
    void * vptr2 =  *(void**)expr2;
    void * vptr3 =  *(void**)expr3;

    std::cout << vptr1 << " ";             
    std::cout << vptr2 << " ";   
    std::cout << vptr3 << std::endl;             

    std::cout << check_equals(expr1, expr2) << " " << check_equals(expr2, expr3) << std::endl;             

    return 0;
}
