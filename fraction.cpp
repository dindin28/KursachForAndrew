#include "fraction.h"
#include "utilities.h"
#include <cmath>
#include <iostream>
#include <string>
#include <numeric>

Fraction::Fraction():numerator(1), denominator(1) {}

Fraction::Fraction(int _numerator, int _denominator)
    :numerator(_numerator), denominator(_denominator){
    GCD(); //Greatest common divisor
}

int Fraction::GCD(){
    long gcd = std::gcd(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    return gcd;
}

int Fraction::getDenominator() { return denominator; }
void Fraction::setDenominator(int a) { denominator = a; }
int Fraction::getNumerator() { return numerator; }
void Fraction::setNumerator(int a) { numerator = a; }

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
    int num2 = a.numerator; 
    num1 *= std::lcm(denominator, a.denominator) / denominator;
    num2 *= std::lcm(denominator, a.denominator) / a.denominator;

    return (num1 < num2);
}

bool Fraction::operator>(const Fraction& a) {
    int num1 = numerator;
    int num2 = a.numerator;
    num1 *= std::lcm(denominator, a.denominator) / denominator;
    num2 *= std::lcm(denominator, a.denominator) / a.denominator;

    return (num1 > num2);
}

bool Fraction::operator==(const Fraction& a) {
    int num1 = numerator;
    int num2 = a.numerator;
    num1 *= std::lcm(denominator, a.denominator) / denominator;
    num2 *= std::lcm(denominator, a.denominator) / a.denominator;

    return (num1 == num2);
}

bool Fraction::operator!=(const Fraction& a) {
    return !(*this == a);
}

Fraction& Fraction::operator+(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;

    numerator *= std::lcm(denominator, _denominator) / denominator;
    _numerator *= std::lcm(denominator, _denominator) / _denominator;

    numerator = numerator + _numerator;
    denominator = std::lcm(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator-(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= std::lcm(denominator, _denominator) / denominator;
    _numerator *= std::lcm(denominator, _denominator) / _denominator;
    numerator = numerator - _numerator;
    denominator = std::lcm(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator-() {
    numerator = -numerator;
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

Fraction gcdForFra(Fraction a, Fraction b) {
    long comDen = std::lcm(a.getDenominator(), b.getDenominator());
    int firNum = a.getNumerator() * (comDen / a.getDenominator());
    int secNum = b.getNumerator() * (comDen / b.getDenominator());
    return Fraction(std::gcd(firNum, secNum), comDen);
}

Fraction& Fraction::operator/(const Fraction& a){
    if (a.denominator == 0 && a.numerator != 0) {
        numerator = 0;
        denominator = 1;
        return *this;
    }
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
    numerator *= std::lcm(denominator, _denominator) / denominator;
    _numerator *= std::lcm(denominator, _denominator) / _denominator;
    numerator = numerator + _numerator;
    denominator = std::lcm(denominator, _denominator);
    GCD();
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& a){
    int _numerator = a.numerator;
    int _denominator = a.denominator;
    numerator *= std::lcm(denominator, _denominator) / denominator;
    _numerator *= std::lcm(denominator, _denominator) / _denominator;
    numerator = numerator - _numerator;
    denominator = std::lcm(denominator, _denominator);
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
    if (a.denominator == 0 && a.numerator != 0) {
        numerator = 0;
        denominator = 1;
        return *this;
    }
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
    } while (strBuff.find_first_not_of("1234567890/-") != std::string::npos);
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