#include <vector>
#include <cassert>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <functional>
 
void printVec(const std::vector<int> &vec)
{
    std::cout << "v= {";
    for (int i : vec)
        std::cout << i << ", ";
    std::cout << "}\n";
}
 
int main()
{
    std::vector<int> v{5, 10, 6, 4, 3, 2, 6, 7, 9, 3};
    printVec(v);
 
    auto m = v.begin() + v.size()/2;
    std::nth_element(v.begin(), m, v.end());
    // std::cout << "\nThe median is " << v[v.size()/2] << '\n';

    auto med = v.begin() + v.size() / 2;
    nth_element(v.begin(), med, v.end());
    // std::cout << "Median: " << *med << "\n";
    printVec(v);
}