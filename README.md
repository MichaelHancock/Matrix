# Matrix
A memory safe C++ matrix template class for image processing and matrix mathematics

---
## How to use in your project?
- Download the matrix.h file to your machine
- Place in your project and include it as you would any other C++ header file *#include "matrix.h"*
## API
### Initialisation
- A empty matrix
-- ```matrix<type>();```
- A matrix with an initial size
-- ```matrix<type>(2, 2);```
-- ```matrix<type>(8, 100);```
- A matrix with an intial size and a default value for each position in the matrix
-- ```matrix<int>(5, 5, 0);```
-- ```matrix<char>(10, 10, 'a');```
- A matrix with the same properties and values of another matrix
-- ```matrix<int> a = matrix<int>(10, 10);``` 
-- ```matrix<int> b = matrix<int>(a);```
### Getting values from the matrix
-- Get a individual from a position in the matrix
--- ```.get(0, 1);``` 
-- Get a individual value from a position in the matrix using overloaded bracket operators: `(` `)`
--- ```myMat(5, 5);```
-- Get a sub-matrix (block) from a larger matrix
--- ```.getBlock(0, 0, 12, 12);```
### Setting values in the matrix
-- Set a individual value at a given position
--- ```.set(0, 5, 'a');```
-- Set a block of values between given positions with a provided value
--- ```.setBlock(0, 0, 10, 10, 'a');```
-- Set a block of values from a given start position with the values of a existing smaller matrix
--- ```.setBlock(4, 4, matrix(2, 2, 'a'));```
### Size
-- Current number of rows
--- ```.rows();``` 
-- Current number of columns
--- ```.columns();```
### Manipulating matrix size and shape
-- Adding a row to the end of the matrix
--- ```.addRow();```
-- Adding a column to the end of the matrix
--- ```.addColumn();```
-- Remove and deallocate all values from the matrix 
--- ```.clear();```
### Miscellaneous
-- Reverse the order of values in the matrix
--- ```.reverse();```
-- Deeply check for equality between two matrix instances
--- ```a == b``` *where `a` and `b` are matrix of the same type*
-- Assign the values of one matrix using another 
--- ```a = b``` *where `a` and `b` are matrix of the same type*