#include "matrix.h"
#include "utilities.h"
#include "fraction.h"

Matrix::Matrix() :rows(0), columns(0), expanded(true) {};

Matrix::Matrix(int _rows, int _columns, bool state)
    :rows(_rows), columns(_columns), expanded(state) {
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

void Matrix::setExpanded(bool state) {expanded = state;}

bool Matrix::getExpanded() { return expanded; }

Matrix Matrix::expandedToMain() {
    Matrix newMatrix(rows, columns - 1, false);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 1; j++) {
            newMatrix.at(j, i) = at(j, i);
        }
    }
    return newMatrix;
}

Matrix Matrix::getMatrixForCramera(int column) {
    Matrix newMatrix(rows, columns - 1, false);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 1; j++) {
            if (j == column) {
                newMatrix.at(j, i) = at(columns - 1, i);
            }
            else {
                newMatrix.at(j, i) = at(j, i);
            }
        }
    }
    return newMatrix;
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

int Matrix::findFirstNonZero(int row) {
    int k = -1;
    do {
        k++;
    } while (at(k, row) == Fraction(0, 1) && k < rows);
    return k;
}

void Matrix::swapRows(int row1, int row2) {
    if (row1 == row2) return void();
    for (int i = 0; i < columns; i++) {
        swapFraction(at(i, row1), at(i, row2));
    }
}

Matrix Matrix::gauss(Fraction* arr, int& size){
    Matrix newMatrix(*this);
    for (int i = 0; i < rows; i++) {
        newMatrix.swapRows(i, newMatrix.findRowWithMax(i, i));
        for (int j = i; j < rows; j++) {
            newMatrix.normalizeRow(j);
            //cout << *this << endl;
        }
        for (int j = i + 1; j < rows; j++) {
            if (newMatrix.findFirstNonZero(i) == newMatrix.findFirstNonZero(j)) {
                newMatrix.subtractRows(i, j);
            }
        }
    }
    size = rows;
    for (int i = rows - 1; i >= 0; i--) {
        arr[i] = newMatrix.at(columns - 1, i);
        for (int j = columns - 2; j > newMatrix.findFirstNonZero(i); j--) {
            Fraction buff(newMatrix.at(j, i));
            arr[i] -= buff * arr[j];
        }
    }
    return newMatrix;
}

void Matrix::checkDenominators() {
    for (int i = 0; i < rows * columns; i++) {
        if (ptr[i].getDenominator() == 0) {
            cout;
        }
    }
}

int Matrix::rowsWithZeros() {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (at(j, i) != Fraction(0, 1)) break;
            if (at(j, i) == Fraction(0, 1) && j == columns - 1) sum++;
        }
    }
    return sum;
}

int Matrix::rang() {
    return rows - rowsWithZeros();
}

bool Matrix::compatibility() {
    Matrix expanded(*this);
    Matrix main = expanded.expandedToMain();
    //cout << main << endl << endl;
    int size;
    Fraction* ptr = new Fraction[columns -1];
    expanded.gauss(ptr, size);
    //cout << expanded << endl << endl;
    main.gauss(ptr, size);
    if (main.rang() < expanded.rang()) return false;
    return true;
}

Fraction Matrix::determinant() {
    Matrix buff(*this);
    Fraction supElement(1, 1);
    for (int k = 0; k < rows; k++) {
        for (int i = 0; i < rows; i++) {
            if (i != k) {
                for (int j = columns - 1; j >= 0; j--) {
                    Fraction buff1(buff.at(k, k));
                    Fraction buff2(buff.at(j, i));
                    Fraction buff3(buff.at(j, k));
                    Fraction buff4(buff.at(k, i));
                    Fraction firPro(buff1 * buff2);
                    Fraction secPro(buff3 * buff4);
                    Fraction diff(firPro - secPro);
                    buff.at(j, i) = diff / supElement;
                }
            }    
        }
        supElement = buff.at(k, k);
    }
    return supElement;
}



int Matrix::getRows() { return rows; }
int Matrix::getColumns() { return columns; }



void Matrix::cramera(Fraction* arr, int& size) {
    size = columns - 1;
    Fraction mainDeterminant = this->determinant();
    for (int i = 0; i < columns - 1; i++) {
        Fraction buff(mainDeterminant);
        Matrix buffMatrix(this->getMatrixForCramera(i));
        arr[i] = buffMatrix.determinant() / buff;
    }
}

void Matrix::normalizeMatrix() {
    Fraction gcd;
    for (int i = 0; i < rows * columns - 1; i++) {
        gcd = gcdForFra(at(i), at(i + 1));
    }
    for (int i = 0; i < rows * columns; i++) {
        at(i) /= gcd;
    }
}

Matrix Matrix::montane(Fraction* arr, int &size) {
    Matrix mat(*this);
    Fraction supElement(1, 1);
    for (int k = 0; k < rows; k++) {
        for (int i = 0; i < rows; i++) {
            if (i != k) {
                for (int j = columns - 1; j >= 0; j--) {
                    Fraction buff1(mat.at(k, k));
                    Fraction buff2(mat.at(j, i));
                    Fraction buff3(mat.at(j, k));
                    Fraction buff4(mat.at(k, i));
                    Fraction firPro(buff1 * buff2);
                    Fraction secPro(buff3 * buff4);
                    Fraction diff(firPro - secPro);
                    mat.at(j, i) = diff / supElement;
                }
            }
        }
        supElement = mat.at(k, k);
    }
    normalizeMatrix();
    size = columns - 1;
    for (int i = 0; i < columns - 1; i++) {
        Fraction buff(mat.at(columns - 1, i));
        arr[i] = buff / supElement;
    }
    return mat;
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
    if (expanded) {
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
                if (x == j && y == i) {
                    int spaces = maxDigits[j] - 1;
                    for (int i = 0; i < spaces; i++) cout << " ";
                    cout << "X" << " ";
                }
                else {
                    int spaces = *(maxDigits + j) - at(j, i).getTotalSymbols();
                    for (int i = 0; i < spaces; i++) cout << " ";
                    cout << at(j, i) << " ";
                }     
            }
            if (x == columns - 1 && y == i) {
                for (int i = 0; i < *(maxDigits + columns - 1) - 1; i++) cout << " ";
                cout << "| " << "X" << endl;
            }
            else cout << "| " << at(columns - 1, i) << endl;
        }
    }
    else {
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
            for (int j = 0; j < columns; j++) {   
                if (j == x && i == y) {
                    int spaces = maxDigits[j] - 1;
                    for (int i = 0; i < spaces; i++) cout << " ";
                    cout << "X" << " ";
                }
                else {
                    int spaces = maxDigits[j] - at(j, i).getTotalSymbols();
                    for (int i = 0; i < spaces; i++) cout << " ";
                    cout << at(j, i) << " ";
                }
            }
            cout << endl;
        }
    }
}

std::ostream& operator<< (std::ostream& out, Matrix& a)
{
    if (a.getExpanded()) {
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
    else {
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
            for (int j = 0; j < a.columns; j++) {
                int spaces = *(maxDigits + j) - a.at(j, i).getTotalSymbols();
                for (int i = 0; i < spaces; i++) out << " ";
                out << a.at(j, i) << " ";
            }
            out << endl;
        }
        return out;
    }
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
    expanded = a.expanded;
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
    :rows(a.rows), columns(a.columns), expanded(a.expanded)
{
    if (a.rows || a.columns) {
        ptr = new Fraction[rows * columns];
        for (int i = 0; i < rows * columns; i++)
            ptr[i] = a.ptr[i];
    }
}