/*
Для ScopedPtr мы запретили копирование, однако, копирование можно и разрешить. Это позволит реализовать более продвинутый умный указатель 
— SharedPtr. Он отличается от ScopedPtr тем, что кроме хранения указателя на объект, он хранит еще и счетчик ссылок (количество объектов 
SharedPtr, которые хранят один и тот же указатель).

Имея такой счетчик, мы можем определить момент, когда на объект, выделенный в куче, не останется больше ссылок (когда счетчик ссылок станет 
равным 0), и освободить память.

Поддержка счетчика ссылок состоит из нескольких частей:

    в конструкторе SharedPtr от ненулевого указателя мы инициализируем счетчик ссылок в 1 (конструктор создает первый SharedPtr, который хранит указатель),
    в конструкторе копирования мы увеличиваем счетчик ссылок на 1, если копируемый SharedPtr содержит ненулевой указатель (конструктор копирования создает еще 
    один SharedPtr с указателем на тот же самый объект),
    в деструкторе мы уменьшаем значение счетчика на 1, если в объекте SharedPtr хранится ненулевой указатель (мы удаляем один SharedPtr, 
    который указывает на объект в куче),
    оператор присваивания уменьшает счетчик ссылок левого операнда на 1, если внутри левого SharedPtr хранится ненулевой указатель, 
    увеличивает счетчик правого SharedPtr на 1, если в правом SharedPtr хранится ненулевой указатель (обычное дело для оператора присваивания — 
    сначала освобождаем старые ресурсы, потом выделяем новые, но при этом нужно быть особенно внимательным с присваиванием самому себе).

Для класса SharedPtr могут оказаться полезными следующие методы (кроме операторов * и ->, конструктора копирования, оператора присваивания, 
деструктора и конструктора):

    метод get, как и в случае со ScopedPtr,
    метод reset — аналогичен reset у ScopedPtr, но освобождает память, только если счетчик ссылок после декремента равен 0.

Реализуйте класс SharedPtr как описано выше. Задание немного сложнее, чем кажется на первый взгляд. Уделите особое внимание "граничным случаям"
— нулевой указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее. 
*/

// $ valgrind --track-origins=yes ./shared_ptr 
// ...
// ==577739== HEAP SUMMARY:
// ==577739==     in use at exit: 0 bytes in 0 blocks
// ==577739==   total heap usage: 10 allocs, 10 frees, 73,776 bytes allocated

#include <iostream>
using namespace std;

struct Expression
{
    Expression(const char *) 
    { /* dummy constructor */ }

    const char * str_ = "dummy struct";
};

struct SharedPtr                                        
{
    explicit SharedPtr(Expression *ptr = 0)
    {   
        ptr_ = ptr;
        if (ptr_ != NULL)
            counter_ = new unsigned (1);    // тут была утечка, не нужно было инициализировать нулем
    }                                       // все равно проверяем указатель всегда

   ~SharedPtr()                                         
    {   
        cout << "del : " << ptr_ << " rc=" << *counter_ << endl;

        if (ptr_ != NULL) {
            --(*counter_); 
            if (*counter_ == 0) {
                delete ptr_;                // удаляем только ненулевые указатели
                delete counter_;            // счетчик тоже в дин. памяти
            }
        }
    }

    SharedPtr(const SharedPtr & other)                  
    {   
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        if (other.ptr_ != NULL)             // если на что-то ссылаемся, то
            ++(*counter_);                  // создание нового указателя копированием 
                                            // увеличивает счетчик ссылок на это что-то
        cout << "copy: " << other.ptr_ << " rc=" << *other.counter_ << endl;                            
    }                                                   

    SharedPtr& operator =(const SharedPtr & other)
    {
        if (ptr_ != other.ptr_) {           // p = p;
            if (ptr_ != NULL) {             // с присвоением ВООБЩЕ ДРУГАЯ история
                --(*counter_);
                if (*counter_ == 0)
                    delete ptr_;
            }
            ptr_ = other.ptr_;              // копируем и нулевые значения тоже
            counter_ = other.counter_;
            if (ptr_ != NULL)                               
                ++(*counter_);              // а вот инкремент, только если ненулевой указатель
            
            cout << "=   : " << ptr_ << " rc=" << *counter_ << endl;  
        }
        return *this;                       // только надо вернуть себя
    }

    Expression* get() const 
    {
        return ptr_;                        // указатель на данные
    }
   
    void reset(Expression *ptr = 0)
    {
        if (ptr_ != NULL) {
            --(*counter_);
            if (*counter_ == 0) {
                delete ptr_;
                delete counter_;
            }
        }

        ptr_ = ptr;
        if (ptr_ != NULL)
            counter_ = new unsigned (1);

        cout << "rst : " << ptr_ << " rc=" << *counter_ << endl;
    }

    Expression& operator*() const
    { 
        return *ptr_;                                   
    }

    Expression* operator->() const
    {
        return ptr_;                                    
    }

private:
    Expression *ptr_;
    // unsigned counter_;                   // почему так не сделать, она же не разделяется? Чтобы рядом в дин.памяти лежало?
    unsigned *counter_;                     // статическую нельзя, т.к. она общая для всех объектов одного класса
};                                          // поэтому указатель, new, delete

int main() {
    SharedPtr p1;
    {
        SharedPtr p2(new Expression("expr1"));
        SharedPtr p3(new Expression("expr2"));
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p3.reset(NULL);
        p3 = p5;
        p5.reset(NULL);
        SharedPtr p6;
        SharedPtr p10(p6);
        SharedPtr p11(p5);
        SharedPtr p7;
        p7 = p7;
        p7.reset(NULL);
        p7.reset(new Expression("expr3"));
        SharedPtr p8(new Expression("expr4"));
        p8.reset(NULL);
    }
    p1 = p1;

    return 0;
}