/*
Начнем с довольно простого случая — рассмотрим динамические объекты, время жизни которых ограничено блоком ({} — 
ограничивают блок в C++). Указатель на такой динамический объект внутри блока можно "связать" со временем жизни объекта 
на стеке: достаточно сохранить этот указатель в некотором объекте на стеке, а в деструкторе этого объекта вызвать delete. 
Так как деструктор объекта, созданного на стеке, вызывается автоматически при выходе из блока, то delete тоже будет вызван 
автоматически.

Такой класс-обертку мы будем называть ScopedPtr. Стоит заметить, что копирование такого объекта может приводить к серьезным 
проблемам, например, к повторному освобождению памяти (два объекта хранят внутри один и тот же указатель и вызов delete будет 
сделан дважды). Поэтому нужно запретить вызов конструктора копирования и оператора присваивания таких объектов. Добиться этого 
можно объявив их в private секции класса. При этом даже не нужно их реализовывать — снаружи класса никто не сможет их вызвать, 
а внутри класса мы этого делать не будем.

Какой интерфейс может быть у такого класса ScopedPtr? Кроме уже известных вам операторов * и ->, деструктора и конструктора, 
полезными могут оказаться следующие методы:

    get — возвращает указатель, сохраненный внутри ScopedPtr (например, чтобы передать его в какую-то функцию);
    release — забирает указатель у ScopedPtr и возвращает значение этого указателя, после вызова release ScopedPtr не должен 
    освобождать память (например, чтобы вернуть этот указатель из функции);
    reset — метод заставляет ScopedPtr освободить старый указатель, а вместо него захватить новый (например, чтобы 
    переиспользовать ScopedPtr, так как оператор присваивания запрещен).
*/

#include <iostream>

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

struct ScopedPtr
{
    explicit ScopedPtr(Expression *ptr = 0)         // запрет неявного приведения типа при создании
    : ptr_(ptr)
    {}

    ~ScopedPtr()
    {
        delete this->ptr_;                          // с удалением указателя со стека очищаются связанные с ним данные
    }

    Expression* get() const 
    {
        return this->ptr_;                          // указатель на данные
    }
    
    Expression* release()
    {
        Expression* p = this->ptr_;                 // указатель обнуляется, но данные не очищаются
        this->ptr_ = NULL;
        return p;
    }
    
    void reset(Expression *ptr = 0)
    {
        delete this->ptr_;                          // данные по указателю очищаются
        this->ptr_ = ptr;
    }

    Expression& operator*() const
    { 
        return *this->ptr_;                         // значение переменной-указателя, т.е. адрес
    }

    Expression* operator->() const
    {
        return this->ptr_;                          // объект-указатель
    }


private:
    // запрещаем копирование и присваивание ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

int main() {

    return 0;
}