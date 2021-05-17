#include <iostream>
#include <iomanip>
#include "utilities.h"
#include <conio.h>
#include "fraction.h"
#include "matrix.h"

using namespace std;

int main(){
    Matrix x(3, 4);
    x.at(0, 0) = Fraction(2, 1);
    x.at(1, 0) = Fraction(4, 1);
    x.at(2, 0) = Fraction(1, 1);
    x.at(3, 0) = Fraction(36, 1);

    x.at(0, 1) = Fraction(5, 1);
    x.at(1, 1) = Fraction(2, 1);
    x.at(2, 1) = Fraction(1, 1);
    x.at(3, 1) = Fraction(47, 1);

    x.at(0, 2) = Fraction(2, 1);
    x.at(1, 2) = Fraction(3, 1);
    x.at(2, 2) = Fraction(4, 1);
    x.at(3, 2) = Fraction(37, 1);
    cout << x;
    //cin >> x;
    x.gauss();
    cout << x << endl << "Press any key";
    _getch();
}