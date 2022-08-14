# z3-learn

## Installation and Build Source

1. Install z3-library via `vcpkg`:

```shell
# clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
# install vcpkg
./vcpkg/bootstrap-vcpkg.sh
# install
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

Start from a simple logical proposition: `P \/ Q`, how can we get the solution make it satisfiable(just let it be `true`)?

The code to solve above problem is as follows:

```cpp
void example_p_union_q()
{
  z3::context c;
  // introduce `p` and `q`
  auto p = c.bool_const("x");
  auto q = c.bool_const("y");
  // `p || q` means `p \/ q`
  // `||` had been overloading, you can also use `z3::operator||`
  auto concentration = (p || q);
  // construct solver from context
  z3::solver solver(c);
  solver.add(concentration);
  std::cout << solver.check() << "\n\n";
  std::cout << solver.get_model() << "\n\n";
}
```

- There are _three_ possible results for `solver.check()`, which are `sat`, `unsat`, `unknown`:
  - `sat`(satisfiability) means there exisits a satisfying solution fore a propositional logic.
  - `unsat`: contrary to `sat`.
  - `unknown`: means something return undefined behavior.
    In above case, `solver.check()` will return `sat`.
- `solver.get_model()` will return the result when `s.check()` is `sat`. In above case, `x` is `true` and `y` is `false` can be extracted.

## Get all solutions of `P \/ Q`

Noticed that `P \/ Q` has more than one solutions which satisfied, but above method only provide 1 solution. To get other solutions, we need to add constraints to `solver` to.

In above case, z3 only output one row in all solutions of `P \/ Q`.

| order | `P` | `Q` | `P \/ Q` |
| ----- | --- | --- | -------- |
| 0     | T   | T   | T        |
| 1     | T   | F   | T        |
| 2     | F   | T   | T        |
| 3     | F   | F   | F        |

Now, we want to get all first 3 rows, in fact, we can get a different from solutions we get before by add negation of each solution given by solve method. And we doing this until no new solution can be found:

```cpp
f = p || q;
while (solver.check() == z3::check_result::sat) {
  f = f && ~(p && q);
  solver.add(f);
  solver.get_model();
}
```

## TODO: sat && validity

Propositional logic is just a small subset of formulas handled by Z3,

## Reference

- [Formal Methods Foundation, by Baojian Hua](https://csslab-ustc.github.io/courses/theory/index.html)
