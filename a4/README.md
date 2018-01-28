Assignment 4:

SAT Solver

This assignment would use MiniSat SAT solver available at https://github.com/agurfinkel/minisat
MiniSat provides a CMake build system. You can compile it using the usual sequence:

cd PROJECT && mkdir build && cd build && cmake ../ && make

The build process creates an executable minisat and a library libminisat.a. You will need link
against the library in your assignment.

Play around with it. Sample files are available in the ece650-minisat repository on GitHub.
Incorporate SAT
Create a polynomial reduction of the decision version of VERTEX COVER to CNF-SAT. We have
discussed the reduction in class. It is also available under the name a4 encoding.pdf on LEARN.
You are allowed to use your own reduction provided it is sound and polynomial-time. Implement
the reduction and use minisat as a library to solve the minimum VERTEX COVER problem for
the graphs that are input to your program (as in Assignment 2).
As soon as you get an input graph via the ’V’ and ’E’ specification you should compute a
minimum-sized Vertex Cover, and immediately output it. The output should just be a sequence of
vertices in increasing order separated by one space each. You can use qsort(3) or std::sort for
sorting.
Assuming that your executable is called ece650-a4, the following is a sample run of your
program:

$ ./ece650-a4

V 5

E {<0,4>,<4,1>,<0,3>,<3,4>,<3,2>,<1,3>}

3 4

The lines starting with V and E are the inputs to your program, and the last line is the output.
Note that the minimum-sized vertex cover is not necessarily unique. You need to output just one
of them.

CMake
As discussed below under "Submission Instructions", you should use a CMakeLists.txt file to build
your project. We will build your project using the following sequence:

cd PROJECT && mkdir build && cd build && cmake ../

where PROJECT is the top level directory of your submission. If your code is not compiled from
scratch (i.e., from the C++ sources), you get an automatic 0.
Submission Instructions

You should place all your files at the top of a GitHub repository. The repository should contain:
• All your C++ source-code files.
• A CMakeLists.txt, that builds your C++ executable ece650-a4.
• A file user.yml that includes your name, WatIAM, and student number. Note that WatIAM
is the user name for your Quest account, e.g. agurfink, and a student number is an 8-digit
number, e.g. 20397238.
See README.md for any additional information.
The submitted files should be at the top of the master branch of your repository.
