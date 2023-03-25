#include <iostream>
#include <algorithm>
#include <vector>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    for (size_t count = 0 ; p != q; ++count) {
        if (count == n) {
            for (FwdIt i = p; ++i != q;)
                *p++ = std::move(*i);
            break;
        }
        ++p;
    }
    return p;
}

// или уот такая мутятя
// template<class FwdIt>
// FwdIt remove_nth(FwdIt start, FwdIt end, size_t n) {
//     return std::remove_if (start, end, 
//         [&n](typename std::iterator_traits<FwdIt>::reference val){ return (n-- == 0); });
// }

// которую можно сократить ...
// template<class FwdIt>
// FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
// {
//     return std::remove_if(p, q, [&n](...) { return 0 == n--; });
// }

int main()
{

    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    
    auto it = remove_nth(v.begin(), v.end(), 5);
    v.erase(it, v.end());
    // auto p = std::remove(prev, p, *prev);
    std::cout << *it << "\n";
    
    for (auto i : v) 
        std::cout << i << " ";
    std::cout << std::endl; // 0 1 2 3 4 6 7 8 9 10

    return 0;
};
