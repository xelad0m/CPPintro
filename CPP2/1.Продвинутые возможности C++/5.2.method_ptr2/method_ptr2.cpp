#include <iostream>

// template <typename T1, typename T2>
// bool compare(T1 const & s1, T1 const & s2, T2 (T1::*mtd) () const) {
//     return ((s1.*mtd)() < (s2.*mtd)());
// }

template <typename T1, typename T2>
constexpr bool compare(const T1& s1, const T1& s2, T2 const mtd)
{
    return (s1.*mtd)() < (s2.*mtd)();
}

int main()
{
    std::string s1("Elf");
    std::string s2("Archer");

    // сравнение строк по длине
    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false
    
    std::cout << "r1=" << r1 << " r2="<< r2 << "\n";

    return 0;
}