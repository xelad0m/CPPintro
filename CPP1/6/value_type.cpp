#include <iostream>
using namespace std;

template <typename T>
class Array
{
    T* data_;
    size_t size_;
public:
    typedef T value_type;                                   // определим синоним для T, тогда в коде Array<int>::value_type -> int

    explicit Array(size_t size, const T& value = T())       // size без умолчания, тогда вызовется К. без параметров
    { 
        size_ = size;
        data_ = (T*) new char [size_ * sizeof(T)];          

        for (int i=0; i<size_ ; ++i)
            new (this->data_ + i) T(value);                 // placement new (в адрес this->data_ + i) помещает тип инициализированный 
                                                            // конструктором копирования экземпляра в ()
    }

    Array()
    {
        this->size_ = 0;
        this->data_ = nullptr;
    }

    Array(const Array & other)
    {   
        this->size_ = other.size_;
        this->data_ = (T*) new char [size_ * sizeof(T)];
    
        for (int i=0; i < this->size_ ; ++i)
            new (this->data_ + i) T( *(other.data_ + i) );
    }
    
    ~Array() 
    {   
        for (int i=0; i < this->size_ ; ++i)
            (this->data_ + i)->~T();

        delete [] ((char *) data_); 
    }

    /*оператор присваивания*/
    Array& operator=(const Array & other)
    {
        if (this != &other)
        {
            this->size_ = other.size_;
            delete ((char *) this->data_);                                 
            data_ = (T*) new char [size_ * sizeof(T)];       
             
            for (int i=0; i < this->size_ ;++i)
                new (this->data_ + i) T( *(other.data_ + i) );
        }
        return *this;
    }
    size_t size() const { return this->size_; }
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }
};

template <class  Container >                               // компилятор догадается, что Container = Array<int> ==> Container::value_type это его поле
bool  contains(Container  const& c,         
               typename  Container::value_type  const& v)  // тогда по имени можем невозбранно получать xранящийся тип
{
    for (int i=0; i < c.size(); ++i)
        if (c[i] == v)
            return true;
    return false;
}

template <class Container, class value_type = typename Container::value_type>   // можно задать шабл.пар.по умолчанию, если в параметрах 
bool contains(Container const& c, value_type arg1, value_type arg2);            // много аргументов и запись будет длинная
               
int  main()
{
    Array <int > a(10, 5);
    cout << contains(a, 5) << endl;

    return  0;
}