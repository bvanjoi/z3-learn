# z3-learn

## Setup

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

2. Build example and run;

```shell
# build
cmake --build build
# run
./build/out
```

## learn z3

TODO: ...