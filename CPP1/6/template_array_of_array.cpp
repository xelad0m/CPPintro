#include <iostream>
using namespace std;

template <typename T, class SizeT = size_t, typename RetT = T>
class Array
{
    T *data_;
    SizeT size_;
public:
    explicit Array(SizeT size) : data_(new T[size]), size_(size) { }
    Array() { };
    ~Array() { delete[] data_; }
    SizeT size() const { return size_; }
    RetT operator[] (SizeT i) const { return data_[i]; }
    T &operator[] (SizeT i) { return data_[i]; }
};

typedef Array<int> Ints;
typedef Array<Ints, size_t, const Ints&> IInts;

int main()
{
    int size = 10;
    IInts abc(size);

    return 0;
}