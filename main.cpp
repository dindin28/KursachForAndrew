#include <iostream>
#include <iomanip>
#include <conio.h>
#include <numeric>
#include <string>
#include "utilities.h"
#include "fraction.h"
#include "matrix.h"

using namespace std;

int main(){
    int columns, rows;
    bool flagOnWrong = false;
    int ch = -1;
    do {
        do {
            clear();
            if (flagOnWrong) {
                cout << "Wrong input, try again" << endl;
            }
            cout << "Matrix have to be square(columns == rows - 1)" << endl;
            cout << "Enter number of expanded matrix columns: ";
            cin >> columns;
            cout << "Enter number of expanded matrix rows: ";
            cin >> rows;
            flagOnWrong = true;
        } while (columns - 1 != rows && columns > 1);
        Matrix matrix(rows, columns, true);
        cout << "Enter your matrix: " << endl;
        cin >> matrix;
        ch = -1;
        while (ch != 8 && ch != 0) {
            do {
                clear();
                cout << "Your matrix: " << endl << matrix;
                cout << "1) See compatibility" << endl;
                cout << "2) See determinant" << endl;
                cout << "3) See matrix after gauss method" << endl;
                cout << "4) See matrix after gauss method and answers" << endl;
                cout << "5) See matrix after montane method" << endl;
                cout << "6) See matrix after montane method and answers" << endl;
                cout << "7) See answers after cramera method" << endl;
                cout << "8) Enter new matrix" << endl;
                cout << "0) Exit program" << endl;
                cin >> ch;
            } while (ch != 0 && ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5 && ch != 6 && ch != 7 && ch != 8);
            switch (ch) {
                case(1): {
                    if (matrix.compatibility())
                        cout << "Matrix is compatibility" << endl;
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(2): {
                    if (matrix.compatibility())
                        cout << "Determinant = " << matrix.determinant() << endl;
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(3): {
                    if (matrix.compatibility()) {
                        Fraction* ptr = new Fraction[matrix.getColumns() - 1];
                        int size = matrix.getColumns() - 1;
                        Matrix x(matrix.gauss(ptr, size));
                        cout << "Matrix after gauss method:" << endl << x;
                    }
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(4): {
                    if (matrix.compatibility()) {
                        Fraction* ptr = new Fraction[matrix.getColumns() - 1];
                        int size = matrix.getColumns() - 1;
                        Matrix x(matrix.gauss(ptr, size));
                        cout << "Matrix after gauss method:" << endl << x;
                        for (int i = 0; i < size; i++) {
                            cout << "x[" << i + 1 << "] = " << ptr[i] << endl;
                        }
                    }
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(5): {
                    if (matrix.compatibility()) {
                        Fraction* ptr = new Fraction[matrix.getColumns() - 1];
                        int size = matrix.getColumns() - 1;
                        Matrix x(matrix.montane(ptr, size));
                        cout << "Matrix after montane method:" << endl << x;
                    }
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(6): {
                    if (matrix.compatibility()) {
                        Fraction* ptr = new Fraction[matrix.getColumns() - 1];
                        int size = matrix.getColumns() - 1;
                        Matrix x(matrix.montane(ptr, size));
                        cout << "Matrix after montane method:" << endl << x;
                        for (int i = 0; i < size; i++) {
                            cout << "x[" << i + 1 << "] = " << ptr[i] << endl;
                        }
                    }
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
                case(7): {
                    if (matrix.compatibility()) {
                        Fraction* ptr = new Fraction[matrix.getColumns() - 1];
                        int size = matrix.getColumns() - 1;
                        matrix.cramera(ptr, size);
                        cout << char(127) << " = " << matrix.determinant() << endl;
                        for (int i = 0; i < size; i++) {
                            Matrix x(matrix.getMatrixForCramera(i));
                            cout << char(127) << i + 1 << " = " << x.determinant() << endl;
                        }
                        for (int i = 0; i < size; i++) {
                            cout << "x[" << i + 1 << "] = " << ptr[i] << endl;
                        }
                    }
                    else
                        cout << "Matrix is not compatibility" << endl;
                    cout << "Press any key";
                    _getch();
                    break;
                }
            }
        }
    } while (ch != 0);
}