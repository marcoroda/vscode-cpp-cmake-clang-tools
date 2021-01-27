#include "Calc_lib/Calc.hpp"
#include <iostream>

int main() {
  std::cout << "Hello from vscode cpp cmake and clang-tools template!!\n";

  Calc mycalc(1, 2);
  auto result = mycalc.multiply();

  std::cout << "Result is: " << result << "\n";

  return 0;
}