# mps

MPS (Multi Precision Simulator) is a tool designed to simulate multi-precision floating-point numbers while capturing differences in computation time. The core idea is to reimplement all binary floating-point operations at the bit level, using boolean values in C++. 

The code shown here represents the main implementations used in my Master’s thesis in Computational Science at the University of Vienna.

## Usage 

To build the project, run:

```
./run_build.sh
```

This script will:
 - Compiles `main.cpp` into the executable `run_main`
 - Build the C++ unit test binary `run_tests`
 - Generates `mps_lib.so`, which can be imported as a Python module

Once the build is complete, you can run the full test suite with:

```
./run_tests.sh
```

This will execute all tests, which are divided into:
 - $1,078$ tests for the C++ code
 - $17$ tests for the Python module

If all tests complete successfully, it is safe to either:
 - Run the compiled binary: `run_main`
 - Import the Python module in your code: `from mps_lib import mps`

### VS Code 

If you are using VS Code, you don’t need to run the run_build.sh script manually. Instead, you can use the built-in CMake Tools extension:

 - Open the Command Palette (`Ctrl + Shift + P`).
 - Run `CMake: Configure`.
 - Run `CMake: Build`.
