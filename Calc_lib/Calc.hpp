#pragma once

class Calc {
 public:
  Calc() = default;
  Calc(int x, int y) : x_(x), y_(y) {}
  int multiply() const;
  int add() const;

 private:
  int x_;
  int y_;
};
