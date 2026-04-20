
# mat2str
## Matrix to String

Header only C++ utility library that turns matrices into strings with optional text labels and binary operators.

Very much WIP, not stable in any meaning of the word

Supports GLM and linalg.h matrices out of the box. NOTE: linalg.h and GLM sources not included, you need to get them yourself and include them before including mat2str.

Can be easily extended to more matrix representations by defining a single overload of *make_internal_mat(matrix_t)* 
that extracts individual elements and stores them in the intermediate, internal format. See mat2str-glm.hpp for an example

Looks like something like this (running exampleMain-basic)
```
Just a lone matrix:

[ 1  2  3 ]
[ 4  5  6 ]
[ 7  8  9 ]

Matrices printed with explicit labels:

     Ints             Floats             doubleMat
[ 1  2  3 ] [ 1.00  2.00  3.00 ] [  2.00   4.00   6.00 ]
[ 4  5  6 ] [ 4.00  5.00  6.00 ] [  8.00  10.00  12.00 ]
[ 7  8  9 ] [ 7.00  8.00  9.00 ] [ 14.00  16.00  18.00 ]

Matrices printed with operators in between:

     Ints               Floats                  Result
[ 1  2  3 ]   [ 1.00  2.00  3.00 ]   [  2.00   4.00   6.00 ]
[ 4  5  6 ] + [ 4.00  5.00  6.00 ] = [  8.00  10.00  12.00 ]
[ 7  8  9 ]   [ 7.00  8.00  9.00 ]   [ 14.00  16.00  18.00 ]

Matrices with variable names as labels:

   intMat             floatMat               doubleMat
[ 1  2  3 ]   [ 1.00  2.00  3.00 ]   [  2.00   4.00   6.00 ]
[ 4  5  6 ] + [ 4.00  5.00  6.00 ] = [  8.00  10.00  12.00 ]
[ 7  8  9 ]   [ 7.00  8.00  9.00 ]   [ 14.00  16.00  18.00 ]


Matrices printed through a matstream object:

     Ints               Floats                  Result
[ 1  2  3 ]   [ 1.00  2.00  3.00 ]   [  2.00   4.00   6.00 ]
[ 4  5  6 ] + [ 4.00  5.00  6.00 ] = [  8.00  10.00  12.00 ]
[ 7  8  9 ]   [ 7.00  8.00  9.00 ]   [ 14.00  16.00  18.00 ]
```

## FAQ
Nobody actually asked, but here we go anyway

Q: Why would anyone need this?\
A: Debug prints. Ever calculate kinematics for a robot?