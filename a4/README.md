Assignment 4:

SAT Solver

This assignment would use MiniSat SAT solver available at https://github.com/agurfinkel/minisat
MiniSat provides a CMake build system. You can compile it using the usual sequence:

cd PROJECT && mkdir build && cd build && cmake ../ && make

$ ./ece650-a4

V 5

E {<0,4>,<4,1>,<0,3>,<3,4>,<3,2>,<1,3>}

3 4

The lines starting with V and E are the inputs to your program, and the last line is the output.
Note that the minimum-sized vertex cover is not necessarily unique. You need to output just one
of them.

Build the project using the following sequence:

cd PROJECT && mkdir build && cd build && cmake ../
