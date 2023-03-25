// определение методов шаблонного класса массива снаружи шаблона класса

// те, которые не могут быть шаблонными (иначе не temp.arg.deduction не работает)
template <typename T>
Array<T>::Array()
{
    size_ = 0;
    data_ = nullptr;
}

template <typename T>
Array<T>::Array(const Array & other)
{
    size_ = other.size_;
    data_ = (T*) new char [size_ * sizeof(T)];
    // placement new
    for (int i=0; i < size_ ; ++i)
        new (data_ + i) T( *(other.data_ + i) );
}

template <typename T>
Array<T>::~Array()
{   
    // placement new delete
    for (int i=0; i < size_ ; ++i)
        (data_ + i)->~T();
    delete [] ((char *) data_); 
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T> & other)
{
    if (this != &other)
    {
        size_ = other.size_;
        delete ((char *) data_);                                 
        data_ = (T*) new char [size_ * sizeof(T)];       
         
        for (int i=0; i < size_ ;++i)
            new (data_ + i) T( *(other.data_ + i) );
    }
    return *this;
}  

// шаблонные методы шаблонного класса массива
template <typename T>  
Array<T>::Array(size_t size, const T& value)   // умолчания могут быть только в объявлении (а тут определение метода)
{
    size_ = size;
    data_ = (T*) new char [size_ * sizeof(T)];          
    for (int i=0; i < size_ ; ++i)
        new (data_ + i) T(value);   
}    

template <typename T>    
T& Array<T>::operator[](size_t i)    
{ return data_[i]; }

template <typename T>
const T& Array<T>::operator[](size_t i) const
{ return data_[i]; }


template <typename T>                           // определение метода шаблонного класса снаружи класса
size_t Array<T>::size() const
{ return size_; }


template <class T>                              // определение "К.копирования" (на самом деле - К.с параметром) снаружи
template <class  Other >                        // т.е. шаблон шаблона по синтаксису
Array<T>::Array( Array <Other > const& other )        
: size_(other.size())
, data_(new  T[other.size()]) 
{
    for(size_t i = 0; i != size_; ++i)
        data_[i] = other[i];
}

template <class T>                              // определение шаблонного "оп.=" снаружи класса
template <class Other>
Array<T> & Array<T>::operator=(const Array <Other> & other)
{        
    if(this != &other) {
        delete [] data_;            
        size_ = other.size_;            
        data_ = new T[size_];            
        for (size_t i = 0; i < size_; i++)
            data_[i] = other.data_[i];                    
    }        
    return *this;
}

// определение прочих шаблонных функций

template <typename Type>
inline void flatten(const Type& item, std::ostream& out)  // определение подходящего шаблона по выводу аргументов (deduce)
{   out << item << " "; }

template <typename Type>
inline void flatten(const Array<Type>& array, std::ostream& out)     
{   
    for (int i=0; i < array.size(); ++i)        // есть метод size()
        flatten(array[i], out);                 // есть оп. []
    out << std::endl;
}

