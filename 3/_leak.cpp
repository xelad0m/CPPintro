struct  IntArray {
    IntArray(int a=0) : size_(a)
    {
        this->data_ = (int *) new int * [size_];
    }
    ~IntArray()
    {
        delete [] this->data_;      //free(): double free detected in tcache 2
    }
private:
    int  size_;
    int *   data_;
};

int  main() {
    IntArray  a1 (10);  // на стеке будет a1.size_ = 10, a1.data-> массив длины 10 в куче
    IntArray  a2 (20);  // аналогично: 20 и ссылка на массив длины 20
    IntArray  a3 = a1;  // копирование (на стеке a3.size_ == 10, a3.data_ == a1.data_)
    a2 = a1;            // присваивание (a2.size_ == 10, a3.data_ == a1.data_)
    return  0;          // итого не стеке 3 объекта, ссылающиеся на один массив в куче
}               // при выходе из функции вызовуются деструкторы a3, a2, a1
