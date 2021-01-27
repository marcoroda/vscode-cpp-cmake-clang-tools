#pragma once

class Calc {
 public:
  Calc() = default;
  Calc(int x, int y) : x_(x), y_(y) {}
  int multiply();
  int add();

 private:
  int x_, y_;
};
