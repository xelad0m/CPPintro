#include <utility>
#include <tuple>
#include <iostream>

/*Напишите шаблонную функцию to_pair, которая принимает произвольный 
std::tuple и два индекса внутри и возвращает std::pair, содержащий 
элементы переданного std::tuple с соответствующими индексами.*/

#if __cplusplus == 201103L // С++11
// template<size_t I, size_t J, typename... Types>
// auto to_pair(std::tuple<Types...> t) -> 
// decltype(std::make_pair(std::get<I>(t), std::get<J>(t)))
// {
//     return std::make_pair(std::get<I>(t), std::get<J>(t));
// }

template<size_t I, size_t J, typename T>
auto to_pair(T const & t) -> 
decltype(std::make_pair(std::get<I>(t), std::get<J>(t)))
{
    return std::make_pair(std::get<I>(t), std::get<J>(t));
}

#elif __cplusplus >= 201402L // С++14
// template<size_t I, size_t J, typename... Types>
// auto to_pair(std::tuple<Types...> const & t) {
//     return std::make_pair(std::get<I>(t), std::get<J>(t));
// }

template<size_t I, size_t J, typename T>
auto to_pair(T const & t) {
    return std::make_pair(std::get<I>(t), std::get<J>(t));
}

#else
#error "Use -std=c++11 or -std=c++14 compiler options."
#endif

int main() {
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t);

    std::cout << std::get<0>(p) << "\n"
              << std::get<1>(p) << "\n";

}