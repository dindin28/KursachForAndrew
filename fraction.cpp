#include "fraction.h"
#include <iostream>

int GCD(int a, int b){
    int div;
    if (a == b)  return a;
    int d = a - b;
    if (d < 0) {
        d = -d;  div = GCD(a, d);
    } else
        div = GCD(b, d); 
    return div;
}

int LCM(int a, int b){
    return a*b / GCD(a, b); 
}

Fraction::Fraction(int _numerator, int _denominator)
    :numerator(_numerator), denominator(_denominator){
    GCD(); //Greatest common divisor
}

int Fraction::GCD(){
    int a = numerator;
    int b = denominator;
        while(a && b) {
        if(a > b)
            a %= b;
        else
            b %= a;
    }
    numerator /= (a+b);
    denominator /= (a+b);
    return a+b;
}

Fraction& Fraction::operator+(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= LCM(denominator, _denominator) / denominator;
    _numerator *= LCM(denominator, _denominator) / _denominator;
    numerator = numerator + _numerator;
    denominator = LCM(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator-(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= LCM(denominator, _denominator) / denominator;
    _numerator *= LCM(denominator, _denominator) / _denominator;
    numerator = numerator - _numerator;
    denominator = LCM(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator*(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= _numerator;
    denominator *= _denominator;
    GCD();
    return *this;
}

Fraction& Fraction::operator/(const Fraction& a){
    int _numerator = a.denominator;
    int _denominator = a.numerator;
    numerator *= _numerator;
    denominator *= _denominator;
    GCD();
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= LCM(denominator, _denominator) / denominator;
    _numerator *= LCM(denominator, _denominator) / _denominator;
    numerator = numerator + _numerator;
    denominator = LCM(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= LCM(denominator, _denominator) / denominator;
    _numerator *= LCM(denominator, _denominator) / _denominator;
    numerator = numerator - _numerator;
    denominator = LCM(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= _numerator;
    denominator *= _denominator;
    GCD();
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& a){
    int _numerator = a.denominator;
    int _denominator = a.numerator;
    numerator *= _numerator;
    denominator *= _denominator;
    GCD();
    return *this;
}

std::ostream& operator<< (std::ostream &out, const Fraction &a)
{
    if(a.denominator == 1){
        out << a.numerator;
    }else if (a.denominator == 0){
        out << "undefined";
    }else{
        out << a.numerator << "/" << a.denominator;
    }
    return out;
}