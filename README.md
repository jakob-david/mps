# mps

MPS (Multi Precision Simulator) is a tool designed to simulate multi-precision floating-point numbers while capturing differences in computation time. The core idea is to reimplement all binary floating-point operations at the bit level, using boolean values in C++. 

The code shown here represents the main implementations used in my Master’s thesis in Computational Science at the University of Vienna.

## Usage 

To build the project, run:

```
./run_build.sh
```

This script will:
 - Compile main.cpp into an executable
 - Build the C++ unit test binary
 - Generate mps_lib.so, which can be imported as a Python module

After the project is built the over $1000$ unit tests can be run by running the following script. This inclued $1078$ tests for the `c++` code and $17$ tests for the python module. : 

```
./run_tests.sh
```
