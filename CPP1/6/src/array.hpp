#pragma once
#include <cstddef>      // size_t
#include <iostream>     // ostream
#include <stdexcept>    // runtime_error

// объявление и определение шаблона класса массива
template <typename T>
class Array                             // теперь определение объявленных тут методов возможно 
{                                       // только снаружи класса с полным путем пространства имен
public:
    // обязательные (не шаблонные)
    Array();                            // К. по-умолчанию
    explicit Array(const Array &);      // К. копирования
    Array& operator=(const Array &);    // оп. присваивания
    ~Array();                           // деструктор

    // необязательные конструкторы
    explicit Array(size_t size, const T& value = T());   // если все параметры с умолчаниями, то это К.по умолчанию и конфликт переопределения конструктора
    
    // не шаблонные методы шаблонного класса
    T& operator[](size_t);    
    const T& operator[](size_t) const;
    
    // шаблонные методы шаблонного класса
    size_t size() const;

    // в т.ч. шаблонные "конструкторы"
    template <class  Other >                    // К. "копирования"
    Array(Array <Other > const&);

    template <class  Other>             
    Array & operator =(Array <Other > const&);  // оп. "присваивания"
private:
    size_t size_;    
    T * data_;
    typedef T value_type;                       // определим синоним для T, тогда в коде Array<int>::value_type -> int
};

// объявление прочих шаблонных функций (по идее инлайн)
template <typename T>
struct Less { bool operator()(T a, T b) const { return b > a; } };      // компаратор по умолчанию

template <typename T>
struct Greater { bool operator()(T a, T b) const { return b < a; } };


template <typename T, class Comp>
T minimum(Array<T> & arr, Comp comp)
{
    T * min = nullptr;                   
    for (int i=0; i < arr.size(); ++i)                  // есть метод size()
        if ( (!min) || comp(arr[i], *min) )             // lazy logic
            min = &arr[i];                              // есть оп. []
    if (!min) throw std::runtime_error("Error: empty array");
    return *min;    
}

template <typename T>
inline void flatten(const T& item, std::ostream& out);  // определение подходящего шаблона по выводу аргументов (deduce)

template <typename T>
inline void flatten(const Array<T>& array, std::ostream& out);


// шаблоны должны объвяляться и определяться в одном (заголовочном) файле
#include "array_impl.hpp"       // разделять можно только вот таким условным образом