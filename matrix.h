#pragma once
class matrix
{
private:
	//Private data members
	int sizeR;
	int sizeC;
	double* data;
	
	//Defualt constructor cannot be called
	matrix();

	/* --- Private member functions --- */
	template <class swappable>
	void swap(swappable &data1, swappable &data2);

public:
	/* --- Constructors --- */

	//Construct matrix object with row and column values
	matrix(int rows, int columns);
	//Construct matrix object with given matrix object (copy constructor)
	matrix(const matrix& mat);
	//Construct matrix object with rows, columns and a intial value
	matrix(int rows, int columns, double value);
	//Construct matrix object with rows, columns and a intial set of values
	matrix(int rows, int columns, double* values);

	/* --- Public member functions --- */

	//Get sum product of all values in matrix
	double sum();
	//Get largest value from matrix
	double max();
	//Get smallest value from matrix
	double min();
	//Get product value from matrix
	double product();
	//Get range value from matrix
	double range();
	//Get mean value from matrix
	double mean();
	//Get standard deviation value from matrix
	double standardDeviation();
	//Get middle value from matrix
	double median();
	//Get count of all rows in matrix
	int rowCount();
	//Get count of all columns in matrix
	int colCount();
	//Get data from a given index in matrix
	double get(int i, int j);
	//Get all data from matrix in array form
	double* getData();
	//Get sub-matrix of data between given coordinates
	matrix getBlock(int row1, int col1, int row2, int col2);
	//Set a single value at given coordinate
	void set(int i, int j, double value);
	//Set a block of data to equal a value
	void setBlock(int row1, int col1, int row2, int col2, double value);
	//Set a block of data to equal values of a given matrix
	void setBlock(int row1, int col1, matrix& mat);
	//Flip matrix about the horizontal axis
	void flipUD();
	//Flip matrix about the vertical axis
	void flipLR();
	//Rotate 90 degrees clockwise
	void rotateClockwise();
	//Convert matrix to binary values using given threshold
	void toBinary(int threshold);
	//Get a binary copy of the current matrix
	matrix getBinary(int threshold);
	//Reverse the order of the values in the matrix 
	void reverse();
	//Sort values of matrix into ascending order
	void sortUp();
	//Sort values of matrix into descending order
	void sortDown();
	//Get an ascending sorted copy of current matrix
	matrix getSortUp();
	//Get an descending sorted copy of current matrix
	matrix getSortDown();
	//Add 1 index thick border of given value
	void addBorder(double borderValue);
	//Remove 1 index thick border from the matrix
	void removeBorder();
	//Check if a value is contained inside the matrix
	bool elem(double element);

	/* --- Public member operator functions ---*/

	matrix operator=(const matrix& mat);
	matrix operator+(const matrix& mat);
	matrix operator-(const matrix& mat);
	matrix operator++();
	matrix operator--();
	bool operator==(const matrix& mat);
	bool operator!=(const matrix& mat);
	matrix operator*(const matrix& mat);
	matrix operator/(const matrix& mat);
	double operator()(int i, int j);

	//Destructor
	~matrix();
};

