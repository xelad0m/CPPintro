#pragma once

#include <memory>

namespace MyLib {
  class MyClass;
  typedef std::shared_ptr<MyClass> MyClassPtr;
}

// тут можно включить все заголовочные файлы ДАННОЙ библиотеки, от которых класс ниже зависит.
// Даже при циклическом включении файлов указатель на класс успеет определиться,
// и в результате к нему можно будет обращаться как в заголовочных файлах, так и в файлах с кодом.

namespace MyLib {
  class MyClass {
    public:
      int data = 42;
  };
}