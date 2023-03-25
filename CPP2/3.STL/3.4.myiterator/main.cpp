#include <iostream>
#include <cassert>

#include <vector>
#include <list>

#include <iterator> // For std::bidirectional_iterator_tag
#include <cstddef>  // For std::ptrdiff_t


// Контейнер VectorList, хранит данные в списке векторов
// (получилось примерно как у всех)
template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

public:

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;
    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;
    ~VectorList() = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q);

    bool empty() const { return size() == 0; } 

    // определите метод size
    size_t size() const 
    {
        // общее количество элементов из всех векторов, которые лежат в списке
        size_t s = 0;
        for (const auto & v : data_)
            s += v.size();       
        return s;
    }

    // определите const_iterator, т.е. такой, что контейнер
    // хранит/возвращает конст. и итератор может только читать
    struct const_iterator {
        // алиасы для итераторов (зависят от шаблонного параметра)
        using listIt            = typename ListT::const_iterator;  
        using vectIt            = typename VectT::const_iterator;

        // вместо наследования от std::iterator (deprecated)
        using iterator_category = std::bidirectional_iterator_tag;      // как во внешнем контейнере ListT
        using difference_type   = std::ptrdiff_t;
        // итератор только константный (изменять на месте нельзя)
        using value_type        = const T;   // const!
        using pointer           = const T*;  // or also value_type*
        using reference         = const T&;  // or also value_type&
        
        // конструкторы
        const_iterator() : data(), list_it(), vect_it() {}
        const_iterator(const const_iterator &it) : data(it.data), list_it(it.list_it), vect_it(it.vect_it) {}
        const_iterator(const ListT *data, listIt lit, vectIt vit) : data(data), list_it(lit), vect_it(vit) {}

        // операторы, необходимые для std::bidirectional_iterator_tag
        const_iterator operator++ (int)                              // postfix
        {   
            if ( data->empty() ) return *this;
            
            auto lend = data->cend();
            auto vend = list_it->cend();
            auto retval = *this;

            if ( vect_it != vend && ++vect_it == vend ) {
                ++list_it;
                if (list_it == lend)
                    --list_it;
                else
                    vect_it = list_it->cbegin();
            }

            return retval;
        }
        const_iterator& operator++ ()                               // prefix
        {
            if ( data->empty() ) return *this;

            auto lend = data->cend();
            auto vend = list_it->cend();

            if ( vect_it != vend && ++vect_it == vend ) {
                ++list_it;
                if (list_it == lend)
                    --list_it;
                else
                    vect_it = list_it->cbegin();
            }

            return *this;
        }        

        const_iterator operator-- (int)                             // postfix
        {
            if ( data->empty() ) return *this;

            auto lbegin = data->cbegin();
            auto vbegin = list_it->cbegin();
            auto retval = *this;

            if ( vect_it == vbegin ) {
                if (list_it != lbegin) {
                    --list_it; 
                    vect_it = list_it->cend();
                }
            }
            if ( vect_it != vbegin )
                --vect_it;

            return retval;
        }                         
        const_iterator& operator--()                                // prefix
        {
            if ( data->empty() ) return *this;

            auto lbegin = data->cbegin();
            auto vbegin = list_it->cbegin();

            if ( vect_it == vbegin ) {
                if (list_it != lbegin) {
                    --list_it; 
                    vect_it = list_it->cend();
                }
            } 
            if ( vect_it != vbegin )
                --vect_it;

            return *this;            
        }                            

        bool operator!= (const const_iterator& it) const { return this->vect_it != it.vect_it;; }
        bool operator== (const const_iterator& it) const { return this->vect_it == it.vect_it; }

        reference operator*() const { return *(this->vect_it); }
        pointer operator->() const { return &(this->vect_it); }
        
        private:
            // храним указатель на данные (внешний контейнер) ...
            ListT const * data; // внутренний класс не имеет доступа к нестатическим полям внешнего, поэтому храним указатель
            // ... и итераторы по внешнему и внутреннему контейнерам
            listIt list_it;     // на какой список указывает итератор 
            vectIt vect_it;     // на какой элемент в списке указывает итератор
    };

    // определите методы begin / end
    const_iterator begin() const 
    { 
        if ( empty() )
            return const_iterator(); // пустой итератор (исп.только в сравнениях begin == end)
        return const_iterator(&data_, data_.cbegin(), data_.cbegin()->cbegin()); // перв.эл.перв.вектора
    } 
    const_iterator end()   const 
    { 
        if ( empty() )
            return const_iterator(); // пустой итератор (исп.только в сравнениях begin == end)
        return const_iterator(&data_, --data_.cend(), (--data_.cend())->cend()); // после (!) посл.эл.посл.вектора
    } 

    // определите const_reverse_iterator (берем готовый шаблон STL)
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend (шаблон сам развернет begin/end)
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()) ; }
    const_reverse_iterator rend()   const { return const_reverse_iterator(begin()) ; }


private:
    ListT data_;
};


// метод, который будет использоваться для заполнения VectorList
// гарантирует, что в списке не будет пустых массивов
template<class T>
template<class It>
void VectorList<T>::append(It p, It q)
{
    if (p != q)
        data_.push_back(VectT(p, q));
} 



int main()
{

    std::cout << "\nTESTS\n\n";

    VectorList<char> vlist;

    // EMPTY
    std::cout << "Empty std::distance(begin,end) = 0 : " << (std::distance(vlist.begin(), vlist.end())) << std::endl;
    std::cout << "Empty size = 0 : " << vlist.size() << std::endl;
    std::cout << "empty() ? 1 : " << vlist.empty() << std::endl;
    std::cout << "begin() == end() ? 1 : " << (vlist.begin() == vlist.end()) << std::endl;
    std::cout << std::endl;

    std::vector<char> v1;
    v1.push_back('A');
    v1.push_back('B');
    v1.push_back('C');

    std::vector<char> v2;
    v2.push_back('D');
    v2.push_back('E');
    v2.push_back('F');
    v2.push_back('G');
    vlist.append(v1.begin(), v1.end());
    vlist.append(v2.begin(), v2.end());

    auto i = vlist.begin();
    auto j = vlist.rbegin();
   
    std::cout << "Size is 7 : " << vlist.size() << std::endl;
    std::cout << "begin is A : " << *i << std::endl;
    std::cout << "std::distance(begin,end) = 7 : " << (std::distance(vlist.begin(), vlist.end())) << std::endl;
    std::cout << "std::distance(begin,begin) = 0 : " << (std::distance(vlist.begin(), vlist.begin())) << std::endl;
    std::cout << "std::distance(end,end) = 0 : " << (std::distance(vlist.end(), vlist.end())) << std::endl;
    std::cout << "*(++begin) == 'B'? 1 : " << (*++vlist.begin() == 'B') << std::endl;
    std::cout << "*(++begin) == 'A'? 0 : " << (*++vlist.begin() == 'A') << std::endl;
    std::cout << std::endl;
    

    std::cout << "rbegin is G : " << *j << std::endl;
    j = --vlist.rend();
    std::cout << "--rend is A : " << *j << std::endl;
    std::cout << std::endl;

    
    std::cout << "Test ++i" << std::endl;
    for (i = vlist.begin(); i != vlist.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "Test i++" << std::endl;
    for (i = vlist.begin(); i != vlist.end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "Test --i" << std::endl;
    for (i = vlist.end(); i != vlist.begin();)
        std::cout << *--i << " ";
    std::cout << std::endl;


    std::cout << "Test i--" << std::endl;
    for (i = vlist.end(); i != vlist.begin();) {
        i--;
        std::cout << *i << " ";
    }
    std::cout << std::endl;
       
    
    std::cout << "Test reverse_const_iterator ++" << std::endl;
    for (j = vlist.rbegin(); j != vlist.rend(); ++j)
        std::cout << *j << " ";
    std::cout << std::endl;


    std::cout << "Test reverse_const_iterator --" << std::endl;
    for ( j = --vlist.rend(); j != vlist.rbegin(); --j )
        std::cout << *j << " ";
    std::cout << *j << std::endl;


    std::cout << std::endl;
	typename VectorList<char>::const_iterator it1 = vlist.begin();
	typename VectorList<char>::const_reverse_iterator rit(it1);
	typename VectorList<char>::const_iterator it2 = rit.base();
	std::cout << ((it1 == it2) ? "base() OK" : "base() failed!") << std::endl;
    
    const VectorList<char>::const_iterator ci_list = vlist.begin();
    VectorList<char>::const_iterator i_list = vlist.begin();
    if (ci_list == i_list) std::cout << "ci_list == i_list, const iterator comparison works fine!\n";

    return 0;
};
