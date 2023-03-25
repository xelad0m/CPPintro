#include <cstddef>          // size_t
#include <algorithm>        // std::swap

/* 
Из шаблонов вроде как не делают библиотеки, т.к. объявление и определение шаблонов должны  
быть в одном файле (обычно заголовочном, который инклюдят куда надо), т.к.
- В точке инстанциирования шаблон должен быть полностью определён.  
    - Поэтому нельзя разделить объявление шаблона в заголовках, определение в коде (!), и поэтому:
- Шаблоны следует определять в заголовочных файлах.  
- Все шаблонные функции (свободные функции и методы) являются inline.  
- В разных единицах трансляции инстанциирование происходит независимо (ленивая компиляция, при первом вхождени).  
- Большие шаблонные классы принято разделять на два заголовочных файла: объявление (array.hpp) и определение(array_impl.hpp).   

    В программе в начале идет #include "array.hpp"
    В конце array.hpp добавляется #include "array_impl.hpp"

Но если очень хочется сделать отдельную либу, можно в файле с кодом прописать конкретные инстансы шаблона, которые должны быть доступны
библиотеке (но это не точно):
    // explicit instantiations
    template class Foo<int>;
    template class Foo<float>;
*/

template<class T>
struct Array
{
    Array() = default;
    explicit Array(size_t size = 0);            // к.с параметром
    explicit Array(size_t size = 0, T const & value = T());
    Array(Array const& a);                      // к.копирования
    Array & operator=(Array const& a);          // оператор присваивания
    virtual ~Array();                                   // деструктор

    size_t size() const;

    T &         operator[](size_t i);           // две версии оператора доступа по индексу
    T const &   operator[](size_t i) const;

    Array (Array && a);                         // перемещающий конструктор
    Array & operator = (Array && a);            // перемещающий оператор присваивания
    
private:    
    size_t  size_;
    T *     data_;   

    void swap(Array & a);                       // вспомогательный метод для перемещения
};



template<class T>
void Array<T>::swap(Array & a) 
/*Вспомогательная функция для перемещающих операций
*/
{
    std::swap(data_, a.data_);
    std::swap(size_, a.size_);
};

template<class T>
Array<T>::Array(Array && a) : size_(0), data_(nullptr)
/*Перемещающий конструктор копирования
*/
{
    swap(a);
    std::cout << "copy move" << std::endl;
}

template<class T>
Array<T>& Array<T>::operator=(Array && a)
/*Перемещающий оператор присваивания
*/
{
    if(a.data_ != data_)
        swap(a);      
    std::cout << "op= move" << std::endl;     
    return *this;
}

template <typename T>
Array<T>::Array(size_t size, T const & value)
/*Конструктор класса, который создает Array размера size, заполненный значениями
  value типа T. Считаем, что у типа T есть конструктор, который можно вызвать без
  без параметров, либо он ему не нужен.
*/
: size_(size), data_(new T[size])
{ 
    for (int i = 0; i < size_ ; ++i)
        data_[i] = value;
}

template <typename T>
Array<T>::Array(Array const & other)
/*Конструктор копирования. Считаем, что для типа T определен оператор присваивания.
*/
{   
    size_ = other.size_;
    data_ = new T [size_];
    for (int i=0; i < size_ ; ++i)
        data_[i] = other.data_[i];
    
    std::cout << "copy" << std::endl;
}
    
template <typename T>
Array<T>::~Array() { delete[] data_; }

template <typename T>
Array<T>& Array<T>::operator=(Array const & other)
/*Оператор присваивания.
*/
{
    if (data_ != other.data_) 
    {
        size_ = other.size_;
        delete[] data_;
        data_ = new T [size_];
        for (int i=0; i < size_ ; ++i)
            data_[i] = other.data_[i];
    }
    
    std::cout << "op= copy" << std::endl;    
    return *this;
}
template <typename T>
size_t Array<T>::size() const { return size_; }


/*Две версии оператора доступа по индексу*/
template<class T>
T& Array<T>::operator[](size_t i) { return data_[i]; }

template<class T>
const T& Array<T>::operator[](size_t i) const { return data_[i]; }