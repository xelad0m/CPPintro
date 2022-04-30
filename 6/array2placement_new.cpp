/*
В предыдущей версии предполагается, что для типа T определены оператор присваивания и конструктор 
по умолчанию. При создании шаблонных классов контейнеров (вроде Array и не только) разумно стараться 
минимизировать требования к типам шаблонных параметров. Поэтому усложним задачу, реализуйте класс 
Array не полагаясь на то, что для типа T определен оператор присваивания и конструктор по умолчанию. 
Конструктор копирования у типа T есть.

Hints: используйте placement new и явный вызов деструктора (смотрите урок 3.4), чтобы создавать и 
уничтожать объекты, аллоцировать правильно выровненную память можно с помощью new char[N * sizeof(T)], 
где N - количество элементов массива.
*/
/*
Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
*/

/*в placement new мы сами указываем адрес. При использовании этой разновидности new нужно в круглых скобках указать аргумент, 
которым будет укажен нужный адрес, и после этого указать тип, ради которого происходит работа с памятью. В целом, синтаксис 
new остаётся таким же, просто между непосредственно new и конечным типом используются круглые скобки, аргументом в которых
 выбирается нужный адрес. Для того, чтобы использовать new placement, обязательно включить заголовочный файл new. Конечно, 
 оно в некоторых реализациях компиляторов может и без этого работать, но это не гарантируется. 
*/

// без placement new результат был идентичный, видимо проверка была чисто на сам метод

#include <iostream>
#include <cstddef>
#include <string>

using namespace std;

template <typename Tx>
struct X
{
	X()
	{
		this->x_ = new Tx();
		*this->x_ = 1;
	}
	X(const X& inX)
	{
		this->x_ = new Tx();  
		*this->x_ = *inX.x_;
	}
	~X() { delete this->x_; }
	friend std::ostream& operator<< (std::ostream& s, const X& obj) 
	{ 
		s << *(obj.x_);
		return s; 
	}

	void set(Tx i) { *(this->x_) = i; }
    const Tx& get() const { return *(this->x_); }
private:
	X& operator=(const X& inX);
	Tx *x_;
};


template <typename T>
class Array
{
    T* data_;
    size_t size_;
public:
    /*конструктор класса, который создает
      Array размера size, заполненный значениями
      value типа T. Если у класса нет конструктора
      по умолчанию, то второй аргумент этого конструктора
      обязателен.*/
    explicit Array(size_t size, const T& value = T())       // size без умолчания, тогда вызовется К. без параметров
    { 
        size_ = size;
        data_ = (T*) new char [size_ * sizeof(T)];          

        for (int i=0; i<size_ ; ++i)
            new (this->data_ + i) T(value);                 // placement new (в адрес this->data_ + i) помещает тип инициализированный 
                                                            // конструктором копирования экземпляра в ()
    }

    /*конструктор класса, который можно вызвать
      без параметров. Должен создавать пустой
      Array.*/
    Array()
    {
        this->size_ = 0;
        this->data_ = nullptr;
    }

    /*конструктор копирования, который создает
      копию параметра. Считайте, что для типа
      T не определен оператор присваивания.*/
    Array(const Array & other)
    {   
        this->size_ = other.size_;
        this->data_ = (T*) new char [size_ * sizeof(T)];
    
        for (int i=0; i < this->size_ ; ++i)
            new (this->data_ + i) T( *(other.data_ + i) );
    }
    
    /*деструктор, если он вам необходим.*/
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

    /*возвращает размер массива (количество
      элементов).*/
    size_t size() const 
    { return this->size_; }

    /*две версии оператора доступа по индексу*/
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    void prnt()
	{
	    for (size_t i = 0; i < size_; ++i)
			cout << *(data_ + i);
		cout << endl;
	}
};

// В класс Array добавить открытый метод:
	// void prnt()
	// {
	//     for (size_t i = 0; i < size_; ++i)
	// 		cout << *(data_ + i);
	// 	cout << endl;
	// }


int main()
{
    typedef X<int> Dummy;
    typedef Array<Dummy> Arr;

    Dummy D;
	D.set(42);
    
    int size = 10;

    Arr a(size, D);            // К. с параметрами
    for (int i=0; i<size; ++i)
        cout << a[i].get() << " ";
    cout <<endl;

    Arr b = a;                 // К. копирования
    for (int i=0; i<size; ++i)
        cout << b[i].get()<< " ";
    cout <<endl;
    
    Arr c;
    c = b;                      // оп. присваивания
    c = c;
    for (int i=0; i<size; ++i)
        cout << c[i].get() << " ";
    cout <<endl;
    
    Arr d;
    d.prnt();


    X<string> x;
	x.set("There are no tests for this task");
	Array<X<string>> *ar = new Array<X<string>>(size_t(1),x );
	ar->prnt();
	Array<X<string>> *xr = ar;
	xr->prnt();
	Array<X<string>> y(*xr);
	y.prnt();
	delete ar;

    return 0;
}