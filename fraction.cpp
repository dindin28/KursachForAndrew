#include "fraction.h"
#include "utilities.h"
#include <cmath>
#include <iostream>
#include <string>

Fraction::Fraction():numerator(1), denominator(1) {}

Fraction::Fraction(int _numerator, int _denominator)
    :numerator(_numerator), denominator(_denominator){
    GCD(); //Greatest common divisor
}

int Fraction::GCD(){
    int a = abs(numerator);
    int b = abs(denominator);
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

int Fraction::getTotalSymbols() {
    if (denominator == 1) {
        if (numerator < 0) {
            return digitsOfNumber(numerator) + 1;
        }
        else {
            return digitsOfNumber(numerator);
        }
    }
    else {
        if (numerator < 0) {
            return digitsOfNumber(numerator) + digitsOfNumber(denominator) + 2;
        }
        else {
            return digitsOfNumber(numerator) + digitsOfNumber(denominator) + 1;
        }
    }
}

bool Fraction::operator<(const Fraction& a) {
    int num1 = numerator;
    int den1 = denominator;
    int num2 = a.numerator;
    int den2 = a.denominator;
    
    num1 *= LCM(den1, den2) / den1;
    num2 *= LCM(den1, den2) / den2;

    return (num1 < num2);
}

bool Fraction::operator>(const Fraction& a) {
    int num1 = numerator;
    int den1 = denominator;
    int num2 = a.numerator;
    int den2 = a.denominator;

    num1 *= LCM(den1, den2) / den1;
    num2 *= LCM(den1, den2) / den2;

    return (num1 > num2);
}

bool Fraction::operator==(const Fraction& a) {
    int num1 = numerator;
    int den1 = denominator;
    int num2 = a.numerator;
    int den2 = a.denominator;

    num1 *= LCM(den1, den2) / den1;
    num2 *= LCM(den1, den2) / den2;

    return (num1 == num2);
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
    if (denominator < 0) {
        denominator = abs(denominator);
        numerator = -numerator;
    }
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
    if (denominator < 0) {
        denominator = abs(denominator);
        numerator = -numerator;
    }
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

std::istream& operator>> (std::istream& in, Fraction& a)
{
    std::string strBuff;
    bool wrongInput = false;
    do {
        if (!wrongInput) {
            std::cout << "Enter fraction (num/den or num): ";
            in >> strBuff;
            wrongInput = true;
        }
        else {
            std::cout << "Wrong format! Enter fraction (num/den or num): ";
            in >> strBuff;
        }  
    } while (strBuff.find_first_not_of("1234567890/") != std::string::npos);
    if (strBuff.find_first_of("/") == std::string::npos) {
        a.numerator = std::stoi(strBuff.substr(0, strBuff.length()));
        a.denominator = 1;
    }
    else {
        a.numerator = std::stoi(strBuff.substr(0, strBuff.find_first_of("/")));
        a.denominator = std::stoi(strBuff.substr(strBuff.find_first_of("/") + 1, strBuff.length()));
    }
    a.GCD();
    return in;
}

void swapFraction(Fraction& a, Fraction& b) {
    if (a == b) return void();
    Fraction buff = a;
    a = b;
    b = buff;
}