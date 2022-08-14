#include <iostream>
#include "z3++.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <string>

std::vector<z3::model> set_all(z3::context &ctx, std::vector<z3::expr> props, z3::expr f)
{
  z3::solver solver(ctx);
  solver.add(f);
  std::vector<z3::model> result = {};
  auto next_f = f;
  while (solver.check() == z3::check_result::sat)
  {
    auto model = solver.get_model();
    result.push_back(model);
    std::vector<z3::expr> blocks = {};
    for (auto prop : props)
    {

      if (model.eval(prop, true).is_true())
      {
        blocks.push_back(prop);
      }
      else
      {
        blocks.push_back(!prop);
      }
    }

    auto next = blocks[0];
    for (int i = 1; i < blocks.size(); i += 1)
    {
      next = next && blocks[i];
    }

    next_f = next_f && !next;

    solver.add(next_f);
  }
  return result;
}

std::vector<z3::model> p_union_q()
{
  z3::context c;
  auto p = c.bool_const("p");
  auto q = c.bool_const("q");

  return set_all(c, {p, q}, p || q);
}

int main()
{
  return 0;
}