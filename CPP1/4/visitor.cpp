#include <iostream>
using namespace std;

/* объявление клиенский классов/структур, чтобы visitor их видел*/
struct Number;
struct BinaryOperation;

/* шаблон проектирования Посетитель*/
struct Visitor {                                                // абстрактный класс
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual ~Visitor() { }
};

/* определение клиентских классов для Посетителя*/
struct Expression
{
    virtual double evaluate() const = 0;                // абстрактный класс
    virtual void visit(Visitor * visitor) const  = 0;   // методы обхода шаблона Посетитель
    virtual ~Expression() { }                           // виртуальный, чтобы определить конкретного потомка в дин.памяти и вызвать его деструктор
};

struct Number : Expression
{
    Number(double value)                                // конструктов, а деструктора тут достаточно встроенного, в дин.памяти полей нет
        : value(value)                      
    {}
    
    double evaluate() const { return value; }           // однажды виртуальный - во всех наследниках тоже виртуальный
    
    void visit(Visitor * visitor) const { visitor->visitNumber(this); }             // методы обхода (по вызывающему типу будет определен адрес метода visit в VMT)

    double get_value() const { return value; }                                      // "нужности" для методов обхода

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

    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }        // методы обхода

    Expression const * get_left()  const { return left; }                               // "нужности" для методов обхода
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

private:
    Expression const * left;
    Expression const * right;
    char op;
};


/* шаблон проектирования Посетитель*/
struct PrintBinaryOperationsVisitor : Visitor {                 // реализация для BinaryOperation
    void visitNumber(Number const * number)
    { }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        bop->get_left()->visit(this);
        std::cout << bop->get_op() << " ";
        bop->get_right()->visit(this);
    }
};

struct PrintVisitor : Visitor {                 
    void visitNumber(Number const * number)
    {   std::cout << number->get_value() << " "; }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        std::cout << "(" << " ";
        bop->get_left()->visit(this);
        std::cout << bop->get_op() << " ";
        bop->get_right()->visit(this);
        std::cout << ")" << " ";
    }
};

int main()
{
    
    Expression * expr1 = new BinaryOperation(new Number(4.5), '*', new Number(3));
    std::cout << expr1->evaluate() << std::endl;
    Expression * expr2 = new BinaryOperation(new Number(3), '+', expr1);
    std::cout << expr2->evaluate() << std::endl;
        
    PrintBinaryOperationsVisitor bop_visitor;
    PrintVisitor expr_visitor;
    
    expr2->visit(&bop_visitor);
    std::cout << std::endl;
    expr2->visit(&expr_visitor);
    std::cout << std::endl;

    return 0;
}
