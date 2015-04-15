#Matrix multiplication routines

##Naive method
- 3 nested for loops in ijk order

##Augented naive methods
#####ikj method
- 3 nested for loops in ikj(!) order

#####transponated method
- right matrix is transponated before multiplication -> both matrices are read in row continous order -> much better cache usage 


##Blocked
- small: 50-100 (template argument) sized blocks read to stack arrays, multiplied, then written back to heap result

##Multithreaed blocked
- every block multiplication is done in a different std:::thread (so there might be lots of threads)


##Strassen-algorithm
- implemented with notation used here:  http://en.wikipedia.org/wiki/Strassen_algorithm
- uses blocked matrix multiplication, when strassen blocks are small (256 defined in Matrix.h)
- It uses stepwise padding of one row-column, when strassen blocks have odd dimension, as described int the second point here: http://en.wikipedia.org/wiki/Strassen_algorithm#Implementation_considerations


---

#Compilation and "testing"

- compile: `g++ -O3 -pthread -std=c++11 -o test testmult.cpp Matrix.h Vector.h`
- test: `./test 1000` , this multiplies 1000x1000 random matrices using different methods and compares results and execution time
