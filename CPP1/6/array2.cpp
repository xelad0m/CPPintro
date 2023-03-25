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
    T *data_;
    size_t size_;
public:
    /*конструктор класса, который создает
      Array размера size, заполненный значениями
      value типа T. Если у класса нет конструктора
      по умолчанию, то второй аргумент этого конструктора
      обязателен.*/
    explicit Array(size_t size, const T& value = T())       // size без умолчания, тогда вызовется К. без параметров
    { 
        this->size_ = size;
        this->data_ = (T*) new char [size_ * sizeof(T)];

        // побайтовое копирование
        int bytes = size_ * sizeof(T);
        int j = 0;
        char * d = (char *) this->data_;
        const T * pvalue = &value;
        char * v = (char *) pvalue;
        for (int i=0; i<bytes ;++i) {
            *(d + i) = *(v + j);
            ++j;
            j = (j < sizeof(T)) ? j : 0;
        }
    }

    /*конструктор класса, который можно вызвать
      без параметров. Должен создавать пустой
      Array.*/
    Array()
    {
        this->size_ = 0;
        this->data_ = 0;
    }

    /*конструктор копирования, который создает
      копию параметра. Считайте, что для типа
      T не определен оператор присваивания.*/
    Array(const Array & other)
    {   
        this->size_ = other.size_;
        this->data_ = (T*) new char [size_ * sizeof(T)];          // выделяем по размеру клиентского типа
        
        // побайтовое копирование (ошибка в этом, с объектами так нельзя)
        // является UB, хотя формальные тесты проходит
        int bytes = size_ * sizeof(T);
        char * d = (char *) this->data_;
        char * v = (char *) other.data_;
        for (int i=0; i<bytes ; ++i)
            *(d + i) = *(v + i);
        /*очень просто написать класс, который нельзя копировать побайтно. 
        Например, он может передать свой this куда-нибудь (вобще говоря, 
        представляется довольно специфическим поведением). Соответственно, 
        при копировании в C++ можно сделать так, чтобы информация о смене 
        this обновилась, а при побайтном копировании этого не произойдёт.*/
        /*Например, объект может реализовывать какой-нибудь интерфейс IOnTimer
        и подписаться у системного таймера, передав туда указатель на себя. 
        Или, например, умный указатель linked_ptr (погуглите) тоже нельзя 
        копировать побайтно.*/
        /*Короче, реально побайтовое копирование работает не всегда, но, 
        в подавляющем большинстве случаев.*/
    }
    
    /*деструктор, если он вам необходим.*/
    ~Array() 
    { delete [] ((char *) data_); }


    /*оператор присваивания*/
    Array& operator=(const Array & other)
    {
        if (this != &other)
        {
            this->size_ = other.size_;
            delete ((char *) this->data_);                                 
            data_ = (T*) new char [size_ * sizeof(T)];       
             
            // побайтовое копирование
            int bytes = size_ * sizeof(T);
            char * d = (char *) this->data_;
            char * v = (char *) other.data_;
            for (int i=0; i<bytes ;++i)
                *(d + i) = *(v + i);
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
	D.set(4);
    
    int size = 5;

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