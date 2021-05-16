#pragma once

#include <iostream>
#include <string>

using namespace std;

int GCD(int a, int b); //greatest common division

int LCM(int a, int b); //least common multiple

class Fraction{
private:
    int numerator;
    int denominator;
public:
    Fraction(int _numerator, int _denominator);
    int GCD();
    Fraction& operator+(const Fraction& a);
    Fraction& operator-(const Fraction& a);
    Fraction& operator*(const Fraction& a);
    Fraction& operator/(const Fraction& a);
    Fraction& operator+=(const Fraction& a);
    Fraction& operator-=(const Fraction& a);
    Fraction& operator*=(const Fraction& a);
    Fraction& operator/=(const Fraction& a);
    friend std::ostream& operator<< (std::ostream &out, const Fraction &a);
};