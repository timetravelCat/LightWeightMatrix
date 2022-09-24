[![Actions Status](https://github.com/InGyu-Choi/LightWeightMatrix/workflows/MacOS/badge.svg)](https://github.com/InGyu-Choi/LightWeightMatrix/actions)
[![Actions Status](https://github.com/InGyu-Choi/LightWeightMatrix/workflows/Windows/badge.svg)](https://github.com/InGyu-Choi/LightWeightMatrix/actions)
[![Actions Status](https://github.com/InGyu-Choi/LightWeightMatrix/workflows/Ubuntu/badge.svg)](https://github.com/InGyu-Choi/LightWeightMatrix/actions)
[![codecov](https://codecov.io/ghInGyu-Choi/LightWeightMatrix/branch/master/graph/badge.svg)](https://codecov.io/ghInGyu-Choi/LightWeightMatrix)
[![GitHub release (latest by date)](https://img.shields.io/github/v/releaseInGyu-Choi/LightWeightMatrix)](https://github.com/InGyu-Choi/LightWeightMatrix/releases)

# LightWeightMatrix

A lightweight template based matrix library.

## Features


## Getting Started

### Prerequisites for Development
* See **DependencyUbuntu.sh**.
* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)
* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*

### Installing

```bash
git clone https://github.com/InGyu-Choi/LightWeightMatrix
cmake --build build --target install --config Release
# a more general syntax for that command is:
cmake --build <build_directory> --target install --config <desired_config>
```

## Building the project

```bash
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target install
```

## Generating the documentation

```bash
mkdir build/ && cd build/
cmake .. -DLightWeightMatrix_ENABLE_DOXYGEN=1 -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target doxygen-docs
```
> ***Note:*** *This will generate a `docs/` directory in the **project's root directory**.*

## Running the tests

By default, the template uses [Catch2](https://github.com/catchorg/Catch2/)
for unit testing. Unit testing can be disabled in the options, by setting the
`ENABLE_UNIT_TESTING` (from
[cmake/StandardSettings.cmake](cmake/StandardSettings.cmake)) to be false. To run
the tests, simply use CTest, from the build directory, passing the desire
configuration for which to run tests for. An example of this procedure is:

```bash
cd build          # if not in the build directory already
ctest -C Release  # or `ctest -C Debug` or any other configuration you wish to test

# you can also run tests with the `-VV` flag for a more verbose output (i.e.
#GoogleTest output as well)
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our how you can
become a contributor and the process for submitting pull requests to us.

## Versioning

This project makes use of [SemVer](http://semver.org/) for versioning. A list of
existing versions can be found in the
[project's releases](https://github.com/InGyu-Choi/LightWeightMatrix/releases).

## Authors

* **InGyu-Choi** - [@InGyu-Choi](https://github.com/InGyu-Choi)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details
