#include <iostream>
#include <iomanip>
#include "utilities.h"
#include <conio.h>
#include "fraction.h"
#include "matrix.h"
#include <numeric>
#include <string>

using namespace std;

int main(){
    Matrix x(4, 6, true);
    x.at(0, 0) = Fraction(3, 1);
    x.at(1, 0) = Fraction(1, 1);
    x.at(2, 0) = Fraction(-2, 1);
    x.at(3, 0) = Fraction(1, 1);
    x.at(4, 0) = Fraction(-1, 1);
    x.at(5, 0) = Fraction(1, 1);

    x.at(0, 1) = Fraction(2, 1);
    x.at(1, 1) = Fraction(-1, 1);
    x.at(2, 1) = Fraction(7, 1);
    x.at(3, 1) = Fraction(-3, 1);
    x.at(4, 1) = Fraction(5, 1);
    x.at(5, 1) = Fraction(2, 1);

    x.at(0, 2) = Fraction(1, 1);
    x.at(1, 2) = Fraction(3, 1);
    x.at(2, 2) = Fraction(-2, 1);
    x.at(3, 2) = Fraction(5, 1);
    x.at(4, 2) = Fraction(-7, 1);
    x.at(5, 2) = Fraction(3, 1);

    x.at(0, 3) = Fraction(3, 1);
    x.at(1, 3) = Fraction(-2, 1);
    x.at(2, 3) = Fraction(7, 1);
    x.at(3, 3) = Fraction(-5, 1);
    x.at(4, 3) = Fraction(8, 1);
    x.at(5, 3) = Fraction(3, 1);

    //Matrix x(3, 4, true);
    cin >> x;
    cout << x;
    x.gauss();
    cout << x << endl << endl << x.compatibility() << endl << "Press any key";
    _getch();
}