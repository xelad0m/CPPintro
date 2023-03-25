#include <iostream>
#include <ostream>
#include <utility>
#include <tuple>



// Напишите метафункцию Fib<N>, которая вычисляет N-ое число Фибоначчи
template<int N>
struct Fib
{
    static int const value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0>
{
    static int const value = 0;
};

template<>
struct Fib<1>
{
    static int const value = 1;
};



// Определение списка целых чисел времени компиляции IntList
template <int ... Ints>
struct IntList;

template <int H, int... T>
struct IntList<H, T...>
{
    static int const Head = H;
    using Tail = IntList<T...>;
};



// определите метафункцию Length для вычисления длины списка
template<typename IL>
struct Length
{
    static int const value = 1 +
        Length<typename IL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
    static int const value = 0;
};



// вывод списка в поток os
template<typename IL>
void printTypeList(std::ostream & os)
{
    os << IL::Head << " "; // это не typename, а член класса
    printTypeList<typename IL::Tail>(os);
};

// вывод пустого списка
template<>
void printTypeList<IntList<>>(std::ostream & os) 
{ os << std::endl; }



// реализация метафункции IntCons позволяет увеличить список на 
// один элемент — он добавляется в начало списка
template<int H, typename TL>
struct IntCons;

template<int H, int... values>
struct IntCons<H, IntList<values...>>
{
    using type = IntList<H, values...>;
};

template<typename TL, int H>
struct ConsInt;

template<int... Ints, int H>
struct ConsInt<IntList<Ints...>, H>
{ using type = IntList<Ints..., H>; };

// генерация списка
template <int N, int ... Next>
struct Generate : public Generate<N-1, N-1, Next...>
{ };

template <int ... Next>
struct Generate<0, Next ... >
 { using type = IntList<Next ... >; };

// вариант генерации
// template<size_t N, int K = 0>
// struct Generate
// {
//     using type = typename IntCons<K, typename Generate<N - 1, K + 1>::type>::type;
// };

// template<int K>
// struct Generate<0, K>
// {
//     using type = IntList<>;
// };

// принимает функтор и кортеж с аргументами для вызова этого функтора и вызывает функтор от этих аргументов
// https://galowicz.de/2016/06/24/integer_sequences_at_compile_time/
template<int N>
using seq = typename Generate<N>::type;

template<typename F, typename TUP, int ...Indexes>
auto apply(F f, TUP t, IntList<Indexes...>)
-> decltype(f(std::get<Indexes>(t)...))
{ return f(std::get<Indexes>(t)...); };

template<typename F, typename ...Ts>
auto apply(F f, std::tuple<Ts...> t) 
-> decltype( apply(f, t, seq<sizeof...(Ts)>{}) )
{ return apply(f, t, seq<sizeof...(Ts)>{}); }

// Напишите метафункцию Zip    

// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;    
};

template <typename A, typename B, template <int, int> class Op>
struct Zip;
 
template <int ...A, int ...B, template <int, int> class Op>
struct Zip<IntList<A...>, IntList<B...>, Op>
{
    using type = IntList<Op<A, B>::value...>;
};



int main()
{
    std::cout << Fib<10>::value << std::endl;     // 55

    using primes = IntList<2,3,5,7,11,13>;
    constexpr int head = primes::Head;
    using odd_primes = primes::Tail;
    constexpr int odd_head = odd_primes::Head;

    std::cout << head << std::endl;
    std::cout << odd_head << std::endl;

    constexpr size_t len = Length<primes>::value;
    std::cout << len << std::endl;


    using L1 = IntList<2,3,4>; 
    printTypeList<L1>(std::cout);
    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>
    printTypeList<L2>(std::cout);
    using L3 = ConsInt<L2, 5>::type;   // IntList<1,2,3,4,5>
    printTypeList<L3>(std::cout);

    using L4 = Generate<5>::type;
    printTypeList<L4>(std::cout);

    // apply
    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5.0, 1.6);     // std::tuple<int, double, double>
    auto res = apply(f, t);                     // 36.6
    std::cout << res << std::endl;

    // два списка одной длины
    using L5 = IntList<1,2,3,4,5>;
    using L6 = IntList<1,3,7,7,2>;

    // результат применения — список с поэлементными суммами
    using L7 = Zip<L5, L6, Plus>::type;  // IntList<2, 5, 10, 11, 7>
    printTypeList<L7>(std::cout);

    return 0;
}