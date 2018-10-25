Sample Run

In the following, we assume that \$" is the shell command-prompt.

$ cd build

$ cmake ../

$ make install

$ cd ./run/bin

$ ./ece650-a3 -s 5 -n 4 -l 5

V = 8

E = {<0,2>,<0,3>,<0,4>,<1,3>,<4,7>,<5,2>,<5,6>}

s 2 4

2-0-4

In the above, the first three lines make it executable, and run the driver program with some
command-line arguments. Then, the lines "V = ...", "E = ...", and "2-0-4" are output. The
input the user provided to your program via stdin is "s 2 4".

Input, Output, and Error

The program would take input from stdin, and output to stdout. Errors would be output to stderr.
Errors would always start with "Error:" followed by a brief description. All the processes would
terminate gracefully (and quietly) once you see EOF at stdin. The program would not generate any
extraneous output; for example, won't print out prompt strings such as "please enter input"
and things like that.

As the example above indicates, there are two kinds of inputs the user provides. One is via the
command-line arguments, like -s and -n switches. This is done only once, when the program is
started. The other input is the 's' command on stdin, which may be issued repeatedly, just as in
Assignment 2. For the 's' command, the program would output a shortest path.

CMake

Build the project using the following sequence:

cd PROJECT && mkdir build && cd build && cmake ../ && make install

where PROJECT is the top level directory of the submission. 

The install target instructs make to
copy all of the binaries (both Python and C++) into directory ./run/bin. This ensures that all
the executable files (including the Python program) are in the same directory.

Python script

I would edit my Python script from Assignment 1 so that its output format for the specification
of the graph matches the input format for my C++ program from Assignment 2. Think of it as
though your Python script provides command-line input to the C++ program. The way to do
this is to simply map each vertex to an index in [0,n-1] (where n is the number of vertices), and
rename your edges accordingly.

Also, the only output that my Python script would produce to stdout is in response to "g",
for which it outputs the specification of the graph (i.e., V and E). Error output should go to stderr.

Cpp program from Assignment 2

I edited it to print the graph that it has read before accepting an s command. This is
necessary so that you know what graph has been produced and what vertexes are available.

Random input generator

The input generator rgen would generate random inputs of street specifications for the
Python script. It takes four command-line arguments. All are optional.

• -s k | where k is an integer ≥ 2. The number of streets should be a random integer in [2; k].
If this option is not specified, you should use a default of k = 10; that is, the number of streets
should be a random integer in [2; 10].

• -n k | where k is an integer ≥ 1. The number of line-segments in each street should be a
random integer in [1; k]. Default: k = 5.

• -l k | where k is an integer ≥ 5. Your process should wait a random number w seconds,
where w is in [5; k] before generating the next (random) input. Default: k = 5.

• -c k | where k is an integer ≥ 1. Your process should generate (x; y) coordinates such that
every x and y value is in the range [−k; k]. For example, if k = 15, all of your coordinate values
should be integers between −15 and 15. Default: k = 20.

The program would generate a specification of streets in the format that your Python script
expects (see Assignment 1). You should ensure
that your input does not have errors. For example, if you generate a line-segment that overlaps
with a line-segment (across all streets) generated earlier, you should regenerate that line-segment.
Similarly, you should not have any zero-length line segments.

Also, note that the random generator could go into an infinite loop looking for a valid specification. You should disallow this from happening by limiting the number of tries. That is, if the random generator fails to generate a valid specification for a continuous A number of attempts, it should
exit() with an error message reported on stderr. A reasonable A to adopt may be 25. Whatever A
you adopt, your error message should mention it. That is, your error message should be something
like, "Error: failed to generate valid input for 25 simultaneous attempts".

Before a new specification to the Python script, the generator should issue "r" commands to
the Python script to remove all previous streets and replace them with the new specification of
3streets.

After generating the input, the generator must issue the "g" command.

Thus, a typical interaction of the random generator is as follows:

1. issue enough r commands to clear any existing street database;

2. issue a commands to add new streets satisfying the specification;

3. issue a g command;

4. wait for specified number of seconds and repeat.

You must use /dev/urandom as the source of your random data. Also, see under \Submission
Instructions" how your executable for the random generator must be named.

Driver

The driver program has the overall control. You have at least three programs that run concurrently:

(1) the random generator, (2) your Python script from Assignment 1, and, (3) your program from
Assignment 2 that takes as input a graph-specification and computes shortest paths. Your driver
program should fork() two processes and exec() two of those programs, and then exec() the
third (so it turns into a process that corresponds to the third program). It would set up all IPC
appropriately beforehand.

It would send normal output to stdout, error output to stderr, and take input from stdin. As
I mentioned above, the only input it takes are "s" commands, that ask for a shortest path between
vertices.
