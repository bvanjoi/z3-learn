#include <iostream>
#include "z3++.h"

void example_p_intersect_q()
{
  z3::context c;
  // introduce `p` and `q`
  auto p = c.bool_const("x");
  auto q = c.bool_const("y");
  // `p /\ q` (operation overloading, you can also use `z3::operator&&`)
  auto intersection = (p && q);
  // construct solver from context
  z3::solver solver(c);
  solver.add(intersection);
  std::cout << solver.check() << "\n\n";
  std::cout << solver.get_model() << "\n\n";
}

int main()
{
  example_p_intersect_q();
}
