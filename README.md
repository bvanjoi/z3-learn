# z3-learn

## Installation and Build Source

1. Install z3-library via `vcpkg`:

```shell
# clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
# install vcpkg
./vcpkg/bootstrap-vcpkg.sh
# install and compile z3
./vcpkg/vcpkg install z3 # it will take some time.
# with cmake
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```

2. Build source code and run:

```shell
# build
cmake --build build
# run
./build/out
```

## Warming Up

Start from a simple logical proposition: `P /\ Q`, how can we get the solution make it satisfiable(just let it be `true`)?

The code to solve above problem is as follows:

```cpp
void example_p_intersect_q()
{
  z3::context c;
  // introduce `p` and `q`
  auto p = c.bool_const("x");
  auto q = c.bool_const("y");
  // `p /\ q` (operation overloading, you can write it as `z3::operator&&(p, q)`)
  auto intersection = (p && q);
  // construct solver from context
  z3::solver solver(c);
  solver.add(intersection);
  std::cout << solver.check() << "\n\n";
  std::cout << solver.get_model() << "\n\n";
}
```

- There are _three_ possible results for `solver.check()`, which are `sat`, `unsat`, `unknown`:
  - `sat`(satisfiability) means there exisits a satisfying solution fore a propositional logic.
  - `unsat`: contrary to `sat`.
  - `unknown`: means something return undefined behavior.
  In above case, `solver.check()` will return `sat`.
- `solver.get_model()` will return the result when `s.check()` is `sat`. In above case, `y` is `true` and `x` is `true` can be extracted.

## TODO: ....

## Reference

- [Formal Methods Foundation, by Baojian Hua](https://csslab-ustc.github.io/courses/theory/index.html)
