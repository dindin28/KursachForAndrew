#include "matrix.h"
#include "utilities.h"
#include "fraction.h"

Matrix::Matrix() :rows(0), columns(0) {};

Matrix::Matrix(int _rows, int _columns)
    :rows(_rows), columns(_columns) {
    ptr = new Fraction[_rows * _columns];
};

Matrix::~Matrix() {
	if (rows || columns) delete[] ptr;
}

int Matrix::findRowWithMax(int column, int row = 0) {
    Fraction max = at(column, row);
    int m_row = row;
    for (int i = row + 1; i < rows; i++) {
        if (max < at(column, i)) {
            max = at(column, i);
            m_row = i;
        }
    }
    return m_row;
}

void Matrix::subtractRows(int row1, int row2) { // row2 - modified
    if (row1 == row2) return void();
    for (int i = 0; i < columns; i++) {
        at(i, row2) -= at(i, row1);
    }
}

void Matrix::normalizeRow(int row) {
    int i = -1;
    do {
        i++;
    } while (i < columns && (Fraction(0, 1) == at(i, row)));
    Fraction divider = Fraction(1, 1) / at(i, row);
    for(; i < columns; i++)
        at(i, row) *= divider;
}

void Matrix::swapRows(int row1, int row2) {
    if (row1 == row2) return void();
    for (int i = 0; i < columns; i++) {
        swapFraction(at(i, row1), at(i, row2));
    }
}

void Matrix::gauss(){
    for (int i = 0; i < rows; i++) {
        swapRows(i, findRowWithMax(i, i));
        for (int j = i; j < rows; j++) {
            normalizeRow(j);
        }
        for (int j = i + 1; j < rows; j++) {
            subtractRows(i, j);
        }
    }
    Fraction* frPtr = new Fraction[rows];
    for (int i = rows - 1; i >= 0; i++) {
        int k = -1;
        do {
            k--;
        } while (at(k, i) == Fraction(0,1));
        frPtr[i] = at(columns - 1, i);

    }
}

bool Matrix::compatibility() {

    return true;
}

Fraction& Matrix::operator[](int index) {
    return *(ptr + index);
}

Fraction& Matrix::at(int index) {
    return *(ptr + index);
}

Fraction& Matrix::at(int x, int y) {
    return *(ptr + y * columns + x);
}

void Matrix::show(int x, int y) {
    int* maxDigits = new int[columns];
    for (int i = 0; i < columns; i++) {
        int max = at(i, 0).getTotalSymbols();
        for (int j = 1; j < rows; j++) {
            if (max < at(i, j).getTotalSymbols())
                max = at(i, j).getTotalSymbols();
        }
        *(maxDigits + i) = max;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 1; j++) {
            int spaces = *(maxDigits + j) - at(j, i).getTotalSymbols();
            for (int i = 0; i < spaces; i++) cout << " ";
            if (x == j && y == i) {
                for (int i = 0; i < *(maxDigits + j) - 1; i++) cout << " ";
                cout << "X" << " "; 
            }
            else cout << at(j, i) << " ";
        }
        if (x == columns - 1 && y == i) {
            for (int i = 0; i < *(maxDigits + columns - 1) - 1; i++) cout << " ";
            cout << "| " << "X" << endl;
        }
        else cout << "| " << at(columns - 1, i) << endl;
    }
}

std::ostream& operator<< (std::ostream& out, Matrix& a)
{
    int* maxDigits = new int[a.columns];
    for (int i = 0; i < a.columns; i++) {
        int max = a.at(i, 0).getTotalSymbols();
        for (int j = 1; j < a.rows; j++) {
            if (max < a.at(i, j).getTotalSymbols())
                max = a.at(i, j).getTotalSymbols();
        }
        *(maxDigits + i) = max;
    }

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns - 1; j++) {
            int spaces = *(maxDigits + j) - a.at(j, i).getTotalSymbols();
            for (int i = 0; i < spaces; i++) out << " ";
            out << a.at(j, i) << " ";
        }
        out << "| " << a.at(a.columns - 1, i) << endl;
    }
    return out;
}

std::istream& operator>> (std::istream& in, Matrix& a)
{
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            clear();
            a.show(j, i);
            cout << "Enter fraction instead X:" << endl;
            in >> a.at(j, i);
        }
    }
    return in;
}

Matrix& Matrix::operator= (const Matrix& a){
    if (this == &a)
        return *this;
    rows = a.rows;
    columns = a.columns;
    if (a.rows || a.columns) {
        ptr = new Fraction[rows * columns];
        for (int i = 0; i < rows * columns; i++)
            ptr[i] = a.ptr[i];
    }
    return *this;
}

Matrix::Matrix(const Matrix& a)
    :rows(a.rows), columns(a.columns)
{
    if (a.rows || a.columns) {
        ptr = new Fraction[rows * columns];
        for (int i = 0; i < rows * columns; i++)
            ptr[i] = a.ptr[i];
    }
}