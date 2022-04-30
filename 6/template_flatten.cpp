/*Шаблонный класс Array может хранить объекты любого типа, для которого определён конструктор копирования, 
в том числе и другой Array, например, Array< Array<int> >. Глубина вложенности может быть произвольной. 
Напишите шаблонную функцию (или несколько) flatten, которая принимает на вход такой "многомерный" Array 
неизвестной заранее глубины вложенности и выводит в поток out через пробел все элементы, хранящиеся на 
самом нижнем уровне. Примеры работы функции flatten:

Array<int> ints(2, 0);
ints[0] = 10;
ints[1] = 20;
flatten(ints, std::cout); // выводит на экран строку "10 20"

Array< Array<int> > array_of_ints(2, ints);
flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"

Array<double> doubles(10, 0.0);
flatten(doubles, std::cout); // работать должно не только для типа int

Note: лидирующие и завершающие пробельные символы будут игнорироваться проверяющей системой, т. е. там 
где ожидается "10 20" будет так же принят, например, вариант "   10 20   ", но не вывод "1020".

Hint: шаблонные функции тоже можно перегружать, из нескольких шаблонных функций будет выбрана наиболее специфичная.*/

// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.


#include <cstddef>
#include <iostream>
using namespace std;


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

template <typename T>
void flatten(const T& item, std::ostream& out)  // определение подходящего шаблона по выводу аргументов (deduce)
{   out << item << " "; }

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)     
{   
    for (int i=0; i < array.size(); ++i)        // есть метод size()
        flatten(array[i], out);                 // есть оп. []
}

// template <typename T>
// void flatten(const T& item, std::ostream& out)     




int main()
{   
    // std::ostream& std::cout (тип std::cout)

    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout);           // выводит на экран строку "10 20"

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout);  // выводит на экран строку "10 20 10 20"

    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout);        // работать должно не только для типа int

    return 0;
}