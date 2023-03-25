#include <iostream>
#include <algorithm>
#include <vector>

#include <functional>
#include <cassert>
#include <numeric>
 
void printVec(const std::vector<int> &vec)
{
    std::cout << "v= {";
    for (int i : vec)
        std::cout << i << ", ";
    std::cout << "}\n";
}
 

// количество перестановок без идущих подряд одинаковых эл-тов
template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    using T = typename std::iterator_traits<Iterator>::value_type;  // тип данных в итераторе
    // тип можно вывести еще уот так уот
    // using T = typename std::decay<decltype (*p)>::type;
    // using T = decltype(&(*p));
    // auto x = *p; using T = decltype(x);

    std::vector<T> v;

    std::copy(p, q, std::back_inserter(v));         // копируем в вектор (вдруг там константы)
    std::sort(v.begin(), v.end());                  // next_permutation нужны упорядоченные элементы

    size_t count = 0;
    do {
        if (std::adjacent_find(v.begin(), v.end()) == v.end())
            count++;
    } while(std::next_permutation(v.begin(), v.end()));
    
    return count;
}


int main()
{
    std::array<int, 3> a1 = {3,2,1};
    size_t c1 = count_permutations(a1.begin(), a1.end());   // 6
    std::cout << c1 << "\n";

    std::array<int, 3> a2 = {1,1,1};
    size_t c2 = count_permutations(a2.begin(), a2.end());   // 0
    std::cout << c2 << "\n";

    std::array<int, 5> a3 = {1,2,3,4,4};
    size_t c3 = count_permutations(a3.begin(), a3.end());   // 36
    std::cout << c3 << "\n";

    return 0;
}