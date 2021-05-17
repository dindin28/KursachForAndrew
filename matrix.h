#ifndef MATRIX_H
#define MATRIX_H

#include "fraction.h"

class Matrix {
private:
	int rows;
	int columns;
	Fraction* ptr;
public:
	Matrix();
	Matrix(int rows, int columns);
	int findRowWithMax(int column, int row);
	void normalizeRow(int row);
	void swapRows(int row1, int row2);
	void gauss();
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