#include <iostream>
#include <list>
#include <iterator>



int main()
{
    std::list<int> l = {1,2,3};
    l.insert(l.begin(), 4);         // 4 1 2 3
    l.insert(l.end(), 5);           // 4 1 2 3 5

    auto it = l.begin();
    ++it;
    ++it;

    l.insert(it, 6);                // 4 1 6 2 3 5

    auto rit1 = l.rbegin();
    ++rit1;
    ++rit1;
    l.insert(rit1.base(), 7);       // 4 1 6 2 7 3 5

    auto rit2 = l.rbegin();
    ++rit2;
    ++rit2;
    l.insert(rit2.base(), 8);       // 4 1 6 2 7 8 3 5

    for (auto item : l)
        std::cout << item << " ";
    std::cout << std::endl;

    return 0;
};
