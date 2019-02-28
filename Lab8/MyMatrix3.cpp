/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 14/02/2019
/// Estimated time to complete: 8 hours
/// Session 1 Start: 09:45 End: 10:00 14/02/2019
/// Session 2 Start: 11:40 End: 12:00 14/02/2019
/// </summary>

#include "MyMatrix3.h"

/// <summary>
/// Default (null) constructor for MyMatrix3
/// </summary>
MyMatrix3::MyMatrix3()
{
	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			m[i][j] = 0.0; // initialise to 0.0
		}
	}
}

/// <summary>
/// Constructor for MyMatrix3 taking in NINE doubles.
/// </summary>
MyMatrix3::MyMatrix3(double t_a11, double t_a12, double t_a13, double t_a21, double t_a22, double t_a23, double t_a31, double t_a32, double t_a33)
{
	m[0][0] = t_a11, m[0][1] = t_a12, m[0][2] = t_a13; // first row
	m[1][0] = t_a21, m[1][1] = t_a22, m[1][2] = t_a23; // second row 
	m[2][0] = t_a31, m[2][1] = t_a32, m[2][2] = t_a33; // third row
}

/// <summary>
/// Constructor for MyMatrix3 taking THREE MyVector3 vectors
/// </summary>
/// <param name="t_row1"></param>
/// <param name="t_row2"></param>
/// <param name="t_row3"></param>
MyMatrix3::MyMatrix3(const MyVector3 t_row1, const MyVector3 t_row2, const MyVector3 t_row3)
{
	m[0][0] = t_row1.x, m[0][1] = t_row1.y, m[0][2] = t_row1.z; // first row
	m[1][0] = t_row2.x, m[1][1] = t_row2.y, m[1][2] = t_row2.z; // second row
	m[2][0] = t_row3.x, m[2][1] = t_row3.y, m[2][2] = t_row3.z; // third row
}

/// <summary>
/// Default destructor for MyMatrix3
/// </summary>
MyMatrix3::~MyMatrix3()
{
}

/// <summary>
/// Converts a MyMatrix3 matrix to an std::string data type
/// </summary>
/// <returns>inputted matrix as a string</returns>
std::string MyMatrix3::toString() const
{
	/*std::string output = "[" + std::to_string(m11) + ", " + std::to_string(m12) + ", " + std::to_string(m13) + "|" + "\n" +
					     "|" + std::to_string(m21) + ", " + std::to_string(m22) + ", " + std::to_string(m23) + "|" + "\n" +
					     "|" + std::to_string(m31) + ", " + std::to_string(m32) + ", " + std::to_string(m33) + "]";*/

	std::string output = "[";

	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			output += std::to_string(m[i][j]); // concatonate value of m[i][j] to string
			if (j < NUM_COLS - 1) output += ", "; // if not last column, add comma
		}
		(i < NUM_ROWS - 1) ? output += "|\n|" : output+= "]"; // if not last row, add | and new line, otherwise add ]
	}

	return output;
}

/// <summary>
/// Checks for equality of two 3x3 matrices
/// </summary>
/// <param name="other">matrix to compare against</param>
/// <returns>true if equal, false otherwise</returns>
bool MyMatrix3::operator==(const MyMatrix3 other) const
{
	bool equal = true;

	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			if (m[i][j] != other.m[i][j]) // if cell doesn't match
			{
				equal = false; // not equal
			}
			if (!equal) break; // if not equal, break out of inner loop
		}
		if (!equal) break; // if not equal, break out of outer loop
	}

	return equal; // return equality
}

/// <summary>
/// Checks for inequality of two 3x3 matrices
/// </summary>
/// <param name="other">matrix to compare against</param>
/// <returns>true if matrices are unequal, otherwise returns false</returns>
bool MyMatrix3::operator!=(const MyMatrix3 other) const
{
	MyMatrix3 left = *this; // assigned left operand via 'this' pointer

	// result assigned inverse of equality operator, as equality is fail quick for true or false
	bool result = !(left == other); 

	return result; // return result
}

/// <summary>
/// Addition operator overload for the addition of TWO 3x3 matrices
/// </summary>
/// <param name="t_other">matrix to add</param>
/// <returns>3x3 matrix representing the sum of both matrices entered</returns>
MyMatrix3 MyMatrix3::operator+(const MyMatrix3 t_other) const
{
	MyMatrix3 result;
	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			result.m[i][j] = m[i][j] + t_other.m[i][j]; // result cell = sum of left cell + right cell
		}
	}

	return result;
}

/// <summary>
/// Subtraction operator overload for the subtraction of one 3x3 matrix from another
/// </summary>
/// <param name="t_other">matrix to subtract</param>
/// <returns></returns>
MyMatrix3 MyMatrix3::operator-(const MyMatrix3 t_other) const
{
	MyMatrix3 result;

	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			result.m[i][j] = m[i][j] - t_other.m[i][j]; // result cell = left cell - right cell
		}
	}

	return result;
}

/// <summary>
/// Multiplication overload to multiply one 3x3 matrix by another
/// </summary>
/// <param name="t_other">matrix to multiply by</param>
/// <returns>3x3 matrix representing the product of the two matrices passed</returns>
MyMatrix3 MyMatrix3::operator*(const MyMatrix3 t_other) const
{
	MyMatrix3 result;
	MyVector3 row;
	MyVector3 column;
	
	for (int i = 0; i < NUM_ROWS; i++) // for each row
	{
		for (int j = 0; j < NUM_COLS; j++) // for each column
		{
			row = { m[i][0],m[i][1],m[i][2] }; // elements 1, 2 and 3 of row i
			column = { t_other.m[0][j],t_other.m[1][j],t_other.m[2][j] }; // elements 1, 2 and 3 of column j
			result.m[i][j] = row.dot(column); // dot product of row i * column j
		}
	}

	return result;
}

/// <summary>
/// Multiplication overload to multiple a 3x1 matrix by a 3D vector (1x3 matrix)
/// </summary>
/// <param name="t_vector">vector to multiply matrix by</param>
/// <returns>vector representing the product of the passed matrices</returns>
MyVector3 MyMatrix3::operator*(const MyVector3 t_vector) const
{
	MyVector3 result;

	result.x = t_vector.dot({ m[0][0],m[0][1],m[0][2] }); // first row by first column
	result.y = t_vector.dot({ m[1][0],m[1][1],m[1][2] }); // second row by first column
	result.z = t_vector.dot({ m[2][0],m[2][1],m[2][2] }); // third row by first column

	return result;
}

/// <summary>
/// Multiplication overload for multiplying a 3x3 matrix by a double scalar
/// </summary>
/// <param name="t_scale">double scalar with which to multiply matrix</param>
/// <returns>3x3 matrix representing the product of the original matrix and the scalar passed</returns>
MyMatrix3 MyMatrix3::operator*(const double t_scale) const
{
	MyMatrix3 result = *this; // left operand via this pointer

	for (int i = 0; i < NUM_ROWS; i++) // for all rows
	{
		for (int j = 0; j < NUM_COLS; j++) // for all columns
		{
			result.m[i][j] *= t_scale; // multiply cell by scalar
		}
	}

	return result;
}

/// <summary>
/// Tranpose a matrix such that the rows of the original become the columns of the returned matrix
/// </summary>
/// <returns>Original matrix transposed row to column</returns>
MyMatrix3 MyMatrix3::transpose() const
{
	// This method works ONLY for a square matrix. 
	// A more generalised solution would take into account the number of rows and columns.

	MyMatrix3 result;

	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			result.m[j][i] = m[i][j]; // transpose m rows into result columns
		}
	}

	return result;
}


/// <summary>
/// Calculates the determinant of a 3x3 matrix
/// </summary>
/// <returns>matrix determinant as a double</returns>
double MyMatrix3::determinant() const
{
	double a = m[0][0], b = m[0][1], c = m[0][2],
		   d = m[1][0], e = m[1][1], f = m[1][2],
		   g = m[2][0], h = m[2][1], i = m[2][2];

	double result = (a*e*i) + (b*f*g) + (c*d*h) - (c*e*g) - (b*d*i) - (a*f*h);

	return result;
}


/// <summary>
/// Determine the inverse of a 3x3 matrix
/// </summary>
/// <returns>MyMatrix3 representing the inverse of the original matrix</returns>
MyMatrix3 MyMatrix3::inverse() const
{
	MyMatrix3 result;
	MyVector3 rows[NUM_ROWS];

	double determinant = this->determinant(); // get determinant of input matrix

	if (determinant != 0)
	{
		// determine adjucate of input matrix
		rows[0] = { m[2][2] * m[1][1] - m[2][1] * m[1][2], m[2][1] * m[0][2] - m[2][2] * m[0][1], m[1][2] * m[0][1] - m[1][1] * m[0][2] };
		rows[1] = { m[2][0] * m[1][2] - m[2][2] * m[1][0], m[2][2] * m[0][0] - m[2][0] * m[0][2], m[1][0] * m[0][2] - m[1][2] * m[0][0] };
		rows[2] = { m[2][1] * m[1][0] - m[2][0] * m[1][1], m[2][0] * m[0][1] - m[2][1] * m[0][0], m[1][1] * m[0][0] - m[1][0] * m[0][1] };

		result = { rows[0],rows[1],rows[2] }; // create 3x3 matrix from rows

		result = result * (1 / determinant); // inverse = 1/determinant(adjucate)
	}

	return result;
}


/// <summary>
/// Returns a given row of a matrix
/// </summary>
/// <param name="t_row">row number to return</param>
/// <returns>row as MyVector3</returns>
MyVector3 MyMatrix3::row(const int t_row) const
{
	MyVector3 result;

	if (t_row >= 0 && t_row < 3)
	{
		result.x = m[t_row][0];
		result.y = m[t_row][1];
		result.z = m[t_row][2];
	}
	else
	{
		result = { 0.0,0.0,0.0 };
	}

	return result;
}

/// <summary>
/// Returns a given column of a matrix
/// </summary>
/// <param name="t_column">column number to return</param>
/// <returns>column as MyVector3</returns>
MyVector3 MyMatrix3::column(const int t_column) const
{
	MyVector3 result;

	if (t_column >= 0 && t_column < 3)
	{
		result.x = m[0][t_column];
		result.y = m[1][t_column];
		result.z = m[2][t_column];
	}
	else
	{
		result = { 0.0,0.0,0.0 };
	}

	return result;
}


///// <summary>
///// Determines the matrix for counter-clockwise rotation about the Z-axis
///// </summary>
///// <param name="t_angleRadians">Angle of rotation</param>
///// <returns>Rotation matrix</returns>
//MyMatrix3 MyMatrix3::rotationZ(const double t_angleRadians)
//{
//	MyVector3 rowOne, rowTwo, rowThree;
//
//	rowOne = { 1.0,0.0,0.0 };
//	rowTwo = { 0.0,cos(t_angleRadians),-sin(t_angleRadians) };
//	rowThree = { 0.0, sin(t_angleRadians),cos(t_angleRadians) };
//
//	MyMatrix3 rotation{ rowOne,rowTwo,rowThree };
//
//	return rotation;
//}
//
///// <summary>
///// Determines the matrix for counter-clockwise rotation about the Y-axis
///// </summary>
///// <param name="t_angleRadians">Angle of rotation</param>
///// <returns>Rotation matrix</returns>
//MyMatrix3 MyMatrix3::rotationY(const double t_angleRadians)
//{
//	MyVector3 rowOne, rowTwo, rowThree;
//
//	rowOne = { cos(t_angleRadians),0.0,sin(t_angleRadians) };
//	rowTwo = { 0.0,1.0,0.0 };
//	rowThree = { -sin(t_angleRadians), 0.0, cos(t_angleRadians) };
//
//	MyMatrix3 result{ rowOne,rowTwo,rowThree };
//
//	return result;
//}
//
//
///// <summary>
///// Determines the matrix for counter-clockwise rotation about the X-axis
///// </summary>
///// <param name="t_angleRadians">Angle of rotation</param>
///// <returns>Rotation matrix</returns>
//MyMatrix3 MyMatrix3::rotationX(const double t_angleRadians)
//{
	//MyVector3 rowOne, rowTwo, rowThree;

	//rowOne = { 1.0,0.0,0.0 };
	//rowTwo = { 0.0,cos(t_angleRadians),-sin(t_angleRadians) };
	//rowThree = { 0.0, sin(t_angleRadians),cos(t_angleRadians) };

	//MyMatrix3 result{ rowOne,rowTwo,rowThree };

	//return result;
//}