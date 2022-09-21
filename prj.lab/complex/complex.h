#include <iostream>
#pragma once
#ifndef COMPLEX_COMPLEX_H_20220309
#define COMPLEX_COMPLEX_H_20220309
class Complex {
public:
	double re, im;
	Complex () { re = 0.0; im = 0.0; }
	Complex (double real) { re = real; im = 0; }
	Complex (double real, double imaginary) { re = real; im = imaginary; }
	Complex operator = (const Complex& copy);
	bool operator == (const Complex& copy) const;
	bool operator != (const Complex& copy) const;
	Complex operator += (const Complex& copy);
	Complex operator -= (const Complex& copy);
	Complex operator *= (const Complex& copy);
	Complex operator /= (const Complex& copy);
	Complex operator - () const;
};
Complex operator + (const Complex& temp, const Complex& copy);
Complex operator - (const Complex& temp, const Complex& copy);
Complex operator * (const Complex& temp, const Complex& copy);
Complex operator / (const Complex& temp, const Complex& copy);
std::ostream& operator << (std::ostream& out, Complex& copy);
std::istream& operator >> (std::istream& in, Complex& copy);
double Division(double real, double imaginary);
#endif