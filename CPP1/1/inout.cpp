#include <iostream>

// int main()
// {
//   int i = 42;
//   double d = 3.14;
//   const char *s = "C-style string";
//   bool flag = true;

//   std::cout << "This is an integer " << i << "\n";
//   std::cout << "This is a double " << d << "\n";
//   std::cout << "This is a \"" << s << "\"\n";
//   std::cout << "This is bool " << flag << "\n";

//   return 0;
// }

int main()
{
  int i = 42;
  double d = 3.14;

  std::cout << "Enter an integer and a double:\n";
  std::cin >> i >> d;   // "a b" - ошибка приведения типа (строка в int) при чтении прерывает ввод, вместо ошибочного значения присваивается 0
  std::cout << "Your input is " << i << ", " << d << "\n";

  return 0;
}