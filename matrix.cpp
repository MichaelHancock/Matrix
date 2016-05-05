#include "matrix.h"
#include <iostream>
#include <math.h>

/* --- Constructors --- */

matrix::matrix()
{//Private constructor cannot be called
}

matrix::matrix(int rows, int columns)
{//Initialise matrix and set all positions to 0
	sizeR = rows;
	sizeC = columns;
	data = new double[sizeR * sizeC];

	for (int i = 0; i < sizeR * sizeC; i++)
		data[i] = 0;
}

matrix::matrix(const matrix& mat)
{//Initialise matrix with existing matrix mat
	sizeR = mat.sizeR;
	sizeC = mat.sizeC;
	data = new double[sizeR * sizeC];

	//Deep copy values from mat.data to data
	for (int i = 0; i < sizeR * sizeC; i++)
		data[i] = mat.data[i];
}

matrix::matrix(int rows, int columns, double value)
{//Initialise matrix and set all positions to value
	sizeR = rows;
	sizeC = columns;
	data = new double[sizeR * sizeC];

	for (int i = 0; i < sizeR * sizeC; i++)
		data[i] = value;
}

matrix::matrix(int rows, int columns, double* values)
{//Initialise matrix and copy data from values
	sizeR = rows;
	sizeC = columns;
	data = new double[sizeR * sizeC];

	for (int i = 0; i < sizeR * sizeC; i++)
		data[i] = values[i];
}

/* -- Private member functions --- */

template <class swappable>
void matrix::swap(swappable & data1, swappable & data2)
{//Swap data values of any type
	swappable holding = data1;
	data1 = data2;
	data2 = holding;
}

/* --- Public member functions --- */

double matrix::sum()
{//Get the sum of all double values in matrix 
	double result = 0;

	for (int i = 0; i < sizeC * sizeR; i++)
		result += data[i];

	return result;
}

double matrix::max()
{//Get largest value from matrix
	double result = data[0];

	for (int i = 0; i < sizeR * sizeC; i++)
	{//Search for larger values
		if (data[i] > result)
			result = data[i];
	}

	return result;
}

double matrix::min()
{//Get smallest value from matrix
	double result = data[0];

	for (int i = 0; i < sizeR * sizeC; i++)
	{//Search for smaller values
		if (data[i] < result)
			result = data[i];
	}

	return result;
}

double matrix::product()
{//Get product value from matrix
	double result = data[0];

	if (data[0] != 0)
		result = data[0];
	else
		return 0;

	for (int i = 1; i < sizeR * sizeC; i++)
	{//Multiply value
		if (data[i] != 0)
			result *= data[i];
		else
			return 0;
	}

	return result;
}

double matrix::range()
{//Get range value from matrix
	return max() - min();
}

double matrix::mean()
{//Get mean value from matrix
	return sum() / (sizeR * sizeC);
}

double matrix::standardDeviation()
{//Get standard Deviation value from matrix
	double result = 0; double current = 0;
	double average = mean();

	for (int i = 0; i < sizeR; i++)
	{//Iterate through rows
		for (int j = 0; j < sizeC; j++)
		{//Iterate through columns
			current = get(i, j) - average;
			current = pow(current, 2);
			result += current;
		}
	}

	//Calculate and return final stage of the stadard deviation
	result /= (sizeR * sizeC);
	return sqrt(result);
}

double matrix::median()
{//Get median value from matrix
	matrix sorted = matrix(sizeR, sizeC);
	sorted = getSortUp();

	if ((sizeR * sizeC) % 2 == 0){
		//Return average of two matrix positions
		int lowIndex = (int)floor((sizeR * sizeC) / 2) - 1;
		int highIndex = (int)floor((sizeR * sizeC) / 2);
		return (sorted.data[highIndex] + sorted.data[lowIndex]) / 2;
	}
	else{
		//Return middle value
		return sorted.data[(sizeR * sizeC) / 2];
	}
}

int matrix::rowCount()
{//Return the number of rows
	return sizeR;
}

int matrix::colCount()
{//Return the number of columns
	return sizeC;
}

double matrix::get(int i, int j)
{//Return the value at a given index
	return data[(i * sizeC) + j];
}

double* matrix::getData()
{//Return all data held in matrix
	return data;
}

matrix matrix::getBlock(int row1, int col1, int row2, int col2)
{//Return a block of matrix data between given coordinates 
	matrix result = matrix(row2 - row1 + 1, col2 - col1 + 1);
	int indexRow = 0;
	int indexCol = 0;

	//Copy values of data between coordinates given into matrix result
	for (int i = row1; i <= row2; i++)
	{//Iterate through rows
		for (int j = col1; j <= col2; j++)
		{//Iterate through columns
			result.set(indexRow, indexCol, get(i, j));
			indexCol++;
		}
		indexRow++;
		indexCol = 0;
	}

	return result;
}

void matrix::set(int i, int j, double value)
{//Set the value of at a given coordinate
	data[(i * sizeC) + j] = value;
}

void matrix::setBlock(int row1, int col1, int row2, int col2, double value)
{//Set the values of a data block between given coordinates
	for (int i = row1; i <= row2; i++)
	{//Iterate through rows
		for (int j = col1; j <= col2; j++)
		{//Iterate through columns
			set(i, j, value);
		}
	}
}

void matrix::setBlock(int row1, int col1, matrix& mat)
{//Set the values of a data block between given coordinates
	int indexRow = 0;
	int indexCol = 0;
	int row2 = row1 + mat.sizeR - 1;
	int col2 = col1 + mat.sizeC - 1;

	for (int i = row1; i <= row2; i++)
	{//Iterate through rows
		for (int j = col1; j <= col2; j++)
		{//Iterate through columns
			set(i, j, mat(indexRow, indexCol));
			indexCol++;
		}
		indexCol = 0;
		indexRow++;
	}
}

void matrix::flipUD()
{//Flip matrix about the horizontal access
	matrix result = matrix(sizeR, sizeC);
	int rowIndex = sizeR - 1;

	for (int i = 0; i < sizeR; i++)
	{//Iterate through rows
		for (int j = 0; j < sizeC; j++)
		{//Iterate through columns
			result.set(i, j, get(rowIndex, j));
		}
		rowIndex--;
	}

	//Set current matrix to equal result
	*this = result;
}

void matrix::flipLR()
{//Flip matrix about the vertical axis
	matrix result = matrix(sizeR, sizeC);
	int colIndex = sizeC - 1;

	for (int i = 0; i < sizeC; i++)
	{//Iterate through columns
		for (int j = 0; j < sizeR; j++)
		{//Iterate through rows
			result.set(j, i, get(j, colIndex));
		}
		colIndex--;
	}

	//Set current matrix to equal result
	*this = result;
}

void matrix::rotateClockwise()
{//Rotate 90 degrees clockwise
	matrix result = matrix(sizeC, sizeR);
	int m = sizeC - 1;
	int n = 0;

	for (int i = 0; i < result.rowCount(); i++)
	{//Iterate through rows
		for (int j = 0; j < result.colCount(); j++)
		{//Iterate through columns
			result.set(i, j, get(m, n));
			m--;
		}
		m = sizeC - 1;
		n++;
	}

	//Set current matrix to equal result
	*this = result;
}

void matrix::toBinary(int threshold)
{//Convert matrix to binary values using given threshold
	for (int i = 0; i < sizeR; i++)
	{//Iterate through rows
		for (int j = 0; j < sizeC; j++)
		{//Iterate through columns
			if (get(i, j) >= threshold)
				set(i, j, 1);
			else
				set(i, j, 0);
		}
	}
}

matrix matrix::getBinary(int threshold)
{//Get a binart copy of current matrix
	matrix result = matrix(sizeR, sizeC);
	for (int i = 0; i < sizeR * sizeC; i++)
		result.data[i] = data[i];

	result.toBinary(threshold);
	return result;
}

void matrix::reverse()
{//Reverse the order of the values in the matrix 
	matrix result = matrix(sizeR, sizeC);
	int j = (sizeR * sizeC) - 1;

	//Copy values into temp.data in reverse order
	for (int i = 0; i < sizeR * sizeC; i++, j--)
		result.data[i] = data[j];

	//Set current matrix to equal result
	*this = result;
}

void matrix::sortUp()
{//Sort values of matrix into ascending order
	for (int i = 0; i < sizeR * sizeC - 1; i++)
	{//Select current value in matrix
		for (int j = i + 1; j < sizeR * sizeC; j++)
		{//Select next value matrix
			if (data[i] > data[j])
				//Swap values if data[i] is greater than data[j]
				swap(data[i], data[j]);
		}
	}
}

void matrix::sortDown()
{//Sort values of matrix into descending order
	for (int i = 0; i < sizeR * sizeC - 1; i++)
	{//Select current value in matrix
		for (int j = i + 1; j > sizeR * sizeC; j++)
		{//Select next value matrix
			if (data[i] > data[j])
				//Swap values if data[i] is greater than data[j]
				swap(data[i], data[j]);
		}
	}
}

matrix matrix::getSortUp()
{//Get an ascending sorted copy of current matrix
	matrix result = matrix(sizeR, sizeC);

	//Deep copy values of current matrix into matrix result
	result = *this;

	//Perform sort
	result.sortUp();

	return result;
}

matrix matrix::getSortDown()
{//Get an descending sorted copy of current matrix
	matrix result = matrix(sizeR, sizeC);

	//Deep copy values of current matrix into matrix result
	result = *this;

	//Perform sort
	result.sortDown();

	return result;
}

void matrix::addBorder(double borderValue)
{//Add 1 index thick border of a given value
	matrix result = matrix(sizeR + 2, sizeC + 2, borderValue);
	result.setBlock(1, 1, *this);

	//Set current matrix to equal result
	*this = result;
}

void matrix::removeBorder()
{//Remove 1 index thick border from the matrix
	if (sizeC < 3 || sizeR < 3)
		return;

	//Set values excluding outer border
	matrix result = matrix(sizeR - 2, sizeC - 2);
	result.setBlock(0, 0, getBlock(1, 1, sizeR - 2, sizeC - 2));

	//Set current matrix to equal result
	*this = result;
}

bool matrix::elem(double element)
{//Check if a value is contained inside the matrix
	for (int i = 0; i < sizeR * sizeC; i++)
	{//Search for element
		if (data[i] == element)
			return true;
	}

	//Element was not found
	return false;
}

/* --- Public Member Operator Functions --- */

matrix matrix::operator=(const matrix& mat)
{//Equals operator
	delete[] data;
	data = new double[mat.sizeC * mat.sizeR];
	sizeC = mat.sizeC;
	sizeR = mat.sizeR;

	//Deep copy values from mat.data to data
	for (int i = 0; i < sizeC * sizeR; i++)
		data[i] = mat.data[i];

	//Return address of current matrix
	return *this;
}

matrix matrix::operator+(const matrix& mat)
{//Addition operator
	matrix result = matrix(sizeR, sizeC);

	//Sum values together and store them in matrix result
	for (int i = 0; i < sizeR * sizeC; i++)
		result.data[i] = data[i] + mat.data[i];

	return result;
}

matrix matrix::operator-(const matrix& mat)
{//Subtraction operator
	matrix result = matrix(sizeR, sizeC);

	//Subtact values and store them in matrix result
	for (int i = 0; i < sizeR * sizeC; i++)
		result.data[i] = data[i] - mat.data[i];

	return result;
}

matrix matrix::operator++()
{//Increment operator
	for (int i = 0; i < sizeR * sizeC; i++)
		data[i]++;

	return *this;
}

matrix matrix::operator--()
{//Decrement operator
	for (int i = 0; i < sizeR * sizeC; i++)
		data[i]--;

	return *this;
}

bool matrix::operator==(const matrix& mat)
{//Logical equals
	bool result = true;

	if ((mat.sizeC * mat.sizeR) != (sizeC * sizeR))
		result = false;
	else{
		//Check for inequality 
		for (int i = 0; i < sizeR * sizeR; i++){
			if (data[i] != mat.data[i])
				result = false;
		}
	}

	return result;
}

bool matrix::operator!=(const matrix& mat)
{//Logical inequals
	bool result = true;

	if ((mat.sizeC * mat.sizeR) != (sizeC * sizeR))
		result = false;
	else{
		//Check for inequality 
		for (int i = 0; i < sizeR * sizeR; i++){
			if (data[i] != mat.data[i])
				result = false;
		}
	}

	return !result;
}

matrix matrix::operator*(const matrix& mat)
{//Multiply operator
	matrix result = matrix(sizeR, sizeC);

	//Multiply values and store them in matrix result
	for (int i = 0; i < sizeR * sizeC; i++)
		result.data[i] = data[i] * mat.data[i];

	return result;
}

matrix matrix::operator/(const matrix& mat)
{//Divide operator
	matrix result = matrix(sizeR, sizeC);

	//Divide values and store them in matrix result
	for (int i = 0; i < sizeR * sizeC; i++){
		//Check for potential divide by zero error
		if (data[i] == 0 || mat.data[i] == 0)
			result.data[i] = 0;
		else
			result.data[i] = data[i] / mat.data[i];
	}

	return result;
}

double matrix::operator()(int i, int j)
{//Brackets operator
	return data[(i * sizeC) + j];
}

/* --- Destructor --- */

matrix::~matrix()
{//Null and deallocate memory
	delete[] data;
	data = NULL;
}
