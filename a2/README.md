Part_2 (Using Dijkstra Algorithm to find the shortest path)

Sample Run:

$mkdir build

$cd build

$cmake ..

$make

$ ./a2-ece650

Input sample_1:

V 15

E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}

s 2 10

(Outcome:

2-8-10)

Input sample_2:

V 5

E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}

s 4 0

(Outcome:

4-1-2-0)

Input, Output, and Error

The program would take input from standard input, and output to standard output. Errors always start with "Error:" followed by a brief description. The program would terminate gracefully (and quietly) once it sees EOF.

As the example above indicates, one kind of input is the specification of a set of vertices V, and
set of edges E of the undirected graph. The specification of a set of vertices starts with 'V', followed
by a space, followed by a positive integer, all in one single line. If the integer that follows the V is
i, then we assume that the vertices are identified by 0, 1, 2,..., i − 1.

The specification for a set of edges starts with 'E'. It then has a space, followed by the set of
edges in a single line delimited by '{' and '}'. The two vertices of an edge are delimited by '<' and
'>' and separated by a comma. The edges in the set are also separated by a comma. There are no
whitespace characters within the { }.

The only other kind of input starts with an 's'. It asks for a shortest path from the first vertex
to the second that is specified after the s. The s is followed by a space, a vertex ID, another space,
and a second vertex ID. The lines 2-8-10 and 4-1-2-0 above are outputs of the s commands that
immediately precede them. If a path does not exist between the vertices, it would output an error.

The graph is specified by the specification of the set of vertices V followed by the set of edges E,
in that order. V and E always occur together. There is no relationship between subsequent graph
specifications; when a new V specification starts, all previous information can be forgotten. After
the specification of the graph there can be zero or more shortest-path queries s. For each s query,
only one shortest path should be output; multiple shortest paths might exist and an arbitrary choice
can be made.
