#include <iostream>
#include "z3++.h"

int main()
{
  z3::context c;
  auto x = c.bool_const("x");
  auto y = c.bool_const("y");
  auto conjecture = (x || y) && (!x || y) && (!x || !y)
  z3::solver s(c);
  // s.add
  // switch (solver.) {

  // }
  cout<<"hello";
  return 0;
}