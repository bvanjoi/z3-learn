#include <iostream>
#include "z3++.h"

int main()
{
  z3::context c;
  auto x = c.bool_const("x");
  auto y = c.bool_const("y");
  auto conjecture = (x || y) && (!x || y) && (!x || !y);
  z3::solver solver(c);
  solver.add(conjecture);
  std::cout << "check: " << solver.check() << std::endl;
  std::cout << "get model: " << solver.get_model() << std::endl;
  return 0;
}
