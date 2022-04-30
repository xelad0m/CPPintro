/*
Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
*/

#include <iostream>
#include <cstddef>

using namespace std;

template <typename T>
class Array
{
    T *data_;
    size_t size_;
public:

    explicit Array(size_t size = 0, const T& value = T())
    /*конструктор класса, который создает
      Array размера size, заполненный значениями
      value типа T. Считайте что у типа T есть
      конструктор, который можно вызвать без
      без параметров, либо он ему не нужен.
    */
    : size_(size), data_(new T[size])
    { 
        for (int i=0; i<size_ ;++i)
            data_[i] = value;
    }

    Array(const Array & other)
    /*конструктор копирования, который создает
      копию параметра. Считайте, что для типа
      T определен оператор присваивания.
    */
    {   
            size_ = other.size_;
            data_ = new T [size_];
            for (int i=0; i < size_ ; ++i)
                data_[i] = other.data_[i];
    }
    
    ~Array() 
    /*деструктор, если он вам необходим.
    */
    { delete[] data_; }

    Array& operator=(const Array & other)
    /*оператор присваивания.
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
        return *this;
    }

    size_t size() const 
    /*возвращает размер массива (количество
      элементов).
    */
    { return size_; }

    /*две версии оператора доступа по индексу*/
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

};

typedef Array<int> Ints;

int main()
{
    Ints a(5, 1);   // констр. с параметрами
    Ints b = a;     // констр. копирования

    for (int i=0; i < a.size(); ++i)
        cout << a[i] << " ";
    cout << endl;    

    for (int i=0; i < b.size(); ++i)
        cout << b[i] << " ";
    cout << endl;    
    
    Ints c;         // констр. по умолчанию (конструктор без параметров мы не делали)
    c = b;

    return 0;
}