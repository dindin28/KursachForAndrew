#ifndef MATRIX_H
#define MATRIX_H

#include "fraction.h"

class Matrix {
private:
	int rows;
	int columns;
	bool expanded;
	Fraction* ptr;
public:
	Matrix();
	Matrix(int rows, int columns, bool state);
	void setExpanded(bool state);
	bool getExpanded();
	Matrix expandedToMain();
	int rowsWithZeros();
	int rang();
	int getRows();
	int getColumns();
	int findFirstNonZero(int row);
	void checkDenominators();
	Matrix getMatrixForCramera(int column);
	int findRowWithMax(int column, int row);
	void normalizeRow(int row);
	void swapRows(int row1, int row2);
	Matrix gauss(Fraction *arr, int& size);
	void cramera(Fraction* arr, int& size);
	Matrix montane(Fraction *arr, int& size);
	void normalizeMatrix();
	Fraction determinant();
	void subtractRows(int row1, int row2);
	bool compatibility(); //סמגלוסעטלמסעü
	Matrix(const Matrix& copy);
	Matrix& operator= (const Matrix& a);
	Fraction& operator[](int index);
	Fraction& at(int index);
	Fraction& at(int x, int y);
	void show(int x, int y);
	friend std::ostream& operator<< (std::ostream& out, Matrix& a);
	friend std::istream& operator>> (std::istream& in, Matrix& a);
	~Matrix();
};

#endif