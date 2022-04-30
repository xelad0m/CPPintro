/*Реализуйте шаблонную функцию minimum, которая находит минимальный элемент, который хранится 
в экземпляре шаблонного класса Array, при этом типовой параметр шаблона Array может быть 
произвольным. Чтобы сравнивать объекты произвольного типа, на вход функции также будет 
передаваться компаратор, в качестве компаратора может выступать функция или объект класса 
с перегруженным оператором "()". 

Примеры вызова функции minimum:
bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };

Array<int> ints(3);
ints[0] = 10;
ints[1] = 2;
ints[2] = 15;
int min = minimum(ints, less); // в min должно попасть число 2
int max = minimum(ints, Greater()); // в max должно попасть число 15*/

// Параметры функции copy_n идут в следующем
// порядке:
//   1. целевой массив
//   2. массив источник
//   3. количество элементов, которые нужно
//      скопировать
//
// Вам нужно реализовать только функцию copy_n,
// чтобы ее можно было вызвать так, как показано
// в примере.

#include <cstddef>
#include <iostream>
// using namespace std;


template <typename T>
class Array
{
    T* data_;
    size_t size_;
public:
    explicit Array(size_t size, const T& value = T())
    { 
        size_ = size;
        data_ = (T*) new char [size_ * sizeof(T)];          
        for (int i=0; i<size_ ; ++i)
            new (this->data_ + i) T(value);                 
    }

    Array() { this->size_ = 0; this->data_ = nullptr; }

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

template <typename Type, class Comp>
Type minimum(Array<Type> & arr, Comp comp)
{
    Type * min = nullptr;                   
    for (int i=0; i < arr.size(); ++i)      // есть метод size()
        if ( (!min) || comp(arr[i], *min) ) // lazy logic
            min = &arr[i];                  // есть оп. []
    if (!min) throw std::runtime_error("Error: ");;                        // нельзя разыменовывать нулевой указатель...
    return *min;    
}

// template <typename Type, class Comp>
// Type & minimum(Array<Type> & arr, Comp comp)
// {
//     Type * min = new Type;   
//     bool zero = true;                
//     for (int i=0; i < arr.size(); ++i)     
//         if ( (zero) || comp(arr[i], *min) ) {
//             min = &arr[i];                 
//             zero = false;
//         }
            
//     if (zero) throw;
//     return *min; 
// }

struct Greater { bool operator()(int a, int b) const { return b < a; } };
bool less(int a, int b) { return a < b; }   // std::less стандартный, поэтому тут нельзя using namespace std; 
                                            // иначе двойное определение less

int main()
{
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less);      // 2
    int max = minimum(ints, Greater()); // 15

    std::cout << min << " " << max << std::endl;
    return 0;
}