ECE650: The project is to help the local police department with their installation of security cameras at traffic intersections. In this assignment, I will solve a particular kind of optimization problem, called the Vertex Cover problem, in this context. The idea is for the police to be able to minimize the number of cameras they need to install, and still be as effective as possible with their monitoring.
Assignment 1:
This is the first in a series of assignments that is part of a single large project.
For this assignment, I need to:
• Take as input a series of commands that describe streets.
• Use that input to construct a particular kind of undirected graph.
• Write the code in Python (Version 2.7.x).
• Ensure that it works on linux system.
Sample Input
The input comprises lines each of which specifies a command. There are 4 kinds of commands.
(1) add a street, (2) change a street, (3) remove a street, and, (4) generate a graph. Here is an
example of how my program should work.
a "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)
a "King Street S" (4,2) (4,8)
a "Davenport Road" (1,4) (5,8)
g
V = {
1: (2,2)
2: (4,2)
3: (4,4)
4: (5,5)
5: (1,4)
6: (4,7)
7: (5,6)
8: (5,8)
9: (3,8)
10: (4,8)
}
E = {
1<1,3>,
<2,3>,
<3,4>,
<3,6>,
<7,6>,
<6,5>,
<9,6>,
<6,8>,
<6,10>
}
c "Weber Street" (2,1) (2,2)
g
V = {
2: (4,2)
5: (1,4)
6: (4,7)
8: (5,8)
10: (4,8)
}
E = {
<2,6>,
<6,5>,
<6,8>,
<6,10>
}
r "King Street S"
g
V = {
}
E = {
}
Commands
• a is used to add a street. It is specified as: \a "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)".
Each (xi, yi) is a GPS coordinate. The coordinates can be interpreted as a poly-line segment. That
is, it draw a line segment from (xi, yi) to (xi+1, yi+1). You are allowed to assume that each
xi and yi is an integer. (Note, however, that the coordinates of an intersection may not be
integers.)
• c is used to change the specification of a street. Its format is the same as for a. It is a new
specification for a street you’ve specified before.
• r is used to remove a street. It is specified as \r "Street Name"".
• g causes the program to output the corresponding graph.
Input and Output
The program take input from standard input, output to the standard
output. Error should be output to standard error
Errors
The above example is that of a \perfect" user -- someone that did not make any mistakes with
specifying the input. If a line in the input is erroneous,
the code would immediately output an error message. The format of the message is to be the string
\Error:" followed by a brief descriptive message about the error. For example:
Error: ’c’ or ’r’ specified for a street that does not exist.
The program would recover from the error as well. That is, the program should reject the
errorneous line, but continue to accept input. The program would not crash because of an error.
Any erroneous input we try will be of a relatively benign nature that mimics honest mistakes a user
makes. We will not try malicious input, such as unduly long lines or weird control characters.
The Output Graph
There is a vertex corresponding to: (a) each intersection, and, (b) the end-point of a line segment of
a street that intersects with another street. An example of (a) from above is Vertex 3. An example
of (b) is Vertex 1. The identity of a vertex can be any string of letters or integers (but no special
characters). For example, v1xyz is acceptable as the identity of a vertex, but not v1 !!#xyz. (The
space is unacceptable, as are ’!’ and ’#’.
There is an edge between two vertices if: (a) at least one of them is an intersection, (b) both
lie on the same street, and, (c) one is reachable from the other without traversing another vertex.
An example from above is the edge <1; 3>, which connects the end-point of a line segment to an
intersection. Another example is the edge <3; 6>, which connects two intersections.# Traffic-lights-management-system
