#include "AudioStream_lib/AudioStream.hpp"
#include "Calc_lib/Calc.hpp"
#include <iostream>
#include <memory>

int main() {
  std::cout << "Hello from vscode cpp cmake and clang-tools template!!\n";

  Calc mycalc(1, 2);
  auto result = mycalc.multiply();

  std::cout << "Result is: " << result << "\n";

  auto p_calc = std::make_unique<Calc>(11, 2);
  auto res = p_calc->division();
  // std::cout << "Result on ptr is: " << result;

  int a;

  return 0;
}