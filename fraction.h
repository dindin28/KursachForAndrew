#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

using namespace std;

class Fraction{
private:
    int numerator;
    int denominator;
public:
    Fraction();
    Fraction(int _numerator, int _denominator);
    int GCD();
    int getTotalSymbols();
    int getDenominator();
    bool operator<(const Fraction& a);
    bool operator>(const Fraction& a);
    bool operator==(const Fraction& a);
    bool operator!=(const Fraction& a);
    Fraction& operator+(const Fraction& a);
    Fraction& operator-(const Fraction& a);
    Fraction& operator*(const Fraction& a);
    Fraction& operator/(const Fraction& a);
    Fraction& operator+=(const Fraction& a);
    Fraction& operator-=(const Fraction& a);
    Fraction& operator*=(const Fraction& a);
    Fraction& operator/=(const Fraction& a);
    friend std::ostream& operator<< (std::ostream &out, const Fraction &a);
    friend std::istream& operator>> (std::istream& in, Fraction& a);
};

void swapFraction(Fraction& a, Fraction& b);

#endif