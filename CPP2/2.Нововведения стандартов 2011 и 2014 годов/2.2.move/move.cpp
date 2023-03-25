#include <iostream>
#include <utility>

class Store {
 public:
  Store() { std::cout << "Default constructor\n"; }

  Store(int x) : px_(new int(x)) { std::cout << "Value constructor\n"; }

  ~Store() {
    delete px_;
    std::cout << "Destructor\n";
  }

  Store(const Store& other) : px_(new int(*other.px_)) {
    std::cout << "Copy constructor\n";
  }

  Store(Store&& other) noexcept : px_(other.px_) {
    other.px_ = nullptr;
    std::cout << "Move constructor\n";
  }

  Store& operator=(const Store& other) {
    Store temp(*other.px_);
    std::swap(px_, temp.px_);
    std::cout << "Copy assignment\n";
    return *this;
  }

  Store& operator=(Store&& other) noexcept {
    Store temp(std::move(other));
    std::swap(px_, temp.px_);
    std::cout << "Move assignment\n";
    return *this;
  }

  void SetX(int x) { *px_ = x; }
  int GetX() const { return *px_; }

  operator bool() { return px_ != nullptr; }

 private:
  int* px_ = nullptr;
};

Store GenStore(int x = 0) {
  Store obj(x);
  return obj;
}

int main() {
  std::cout << "Store sx(4): ";
  Store sx(4);
  

  if (sx) {
    std::cout << "sx is not null\n";
  }
  std::cout << "---------End of operation---------\n\n";

  std::cout << "Store s1(sx): ";
  Store s1(sx);
  std::cout << "---------End of operation---------\n\n";

  std::cout << "Store s2(std::move(sx)): ";
  Store s2(std::move(sx));
  if (!sx) {
    std::cout << "sx is null\n";
  }
  std::cout << "---------End of operation---------\n\n";

  std::cout << "Store s3: ";
  Store s3;
  std::cout << "---------End of operation---------\n\n";

  std::cout << "s3 = s1: ";
  s3 = s1;
  std::cout << "---------End of operation---------\n\n";

  std::cout << "Store s4 = std::move(s3): ";
  Store s4 = std::move(s3);
  if (!s3) {
    std::cout << "s3 is null\n";
  }
  std::cout << "---------End of operation---------\n\n";

  std::cout << "Store s5 = GenStore(): ";
  Store s5 = GenStore();
  std::cout << "---------End of operation---------\n\n";

  std::cout << "s5 = GenStore(): ";
  s5 = GenStore();
  std::cout << "---------End of operation---------\n\n";

  // добавьте свои тесты
  return 0;
}