#include <iostream>
#include <complex/complex.h>
#include <limits>
Complex Complex::operator = (const Complex& copy){
	re = copy.re;
	im = copy.im;
	return *this;
}
Complex Complex::operator += (const Complex& copy) {
	re += copy.re;
	im += copy.im;
	return *this;
}
Complex Complex:: operator -() const {
	return Complex{ -re, -im };
}
Complex Complex:: operator -= (const Complex& copy) {
	return *this += -copy;
}
Complex Complex:: operator *= (const Complex& copy) {
	Complex temp = *this;
	re = temp.re * copy.re - temp.im * copy.im;
	im = temp.re * copy.im + temp.im * copy.re;
	return *this;
}
double Division(double real, double imaginary) {
	if (imaginary == 0) {
		throw "Division error by zero!";
	}
	return real / imaginary;
}
Complex Complex:: operator /= (const Complex& copy) {
	Complex temp = *this;
	double zn = copy.re * copy.re + copy.im * copy.im;
	if (zn == 0){ throw std::invalid_argument("Division error by zero"); }
	re = (temp.re * copy.re + temp.im * copy.im) / zn;
	im = (temp.im * copy.re - temp.re * copy.im) / zn;
	return *this;
}
Complex operator + (const Complex& temp, const Complex& copy) {
	Complex temp_t = temp;
	return temp_t += copy;
}
Complex operator - (const Complex& temp, const Complex& copy) {
	Complex temp_t = temp;
	return temp_t -= copy;
}
Complex operator * (const Complex& temp, const Complex& copy) {
	Complex temp_t = temp;
	return temp_t *= copy;
}
Complex operator / (const Complex& temp, const Complex& copy) {
	Complex temp_t = temp;
	return temp_t /= copy;
}
bool Complex::operator == (const Complex& copy) const {
	return (abs(this->im - copy.im) < 2 * std::numeric_limits<double>::epsilon()) && (abs(this->re - copy.re) < 2 * std::numeric_limits<double>::epsilon());
}
bool Complex::operator != (const Complex& copy) const {
	return !(*this == copy);
}
std::ostream& operator << (std::ostream& out, Complex& copy) {
	out << "{"<< copy.re << "," << copy.im << "}";
	return out;
}
std::istream& operator >> (std::istream& in, Complex& copy) {
	char left(0);
	double real(0.0);
	char separator(0);
	double imaginary(0.0);
	char right(0);
	in >> left >> real >> separator >> imaginary >> right;
	if (in.good()) {
		if (left == '{' && separator == ',' && right == '}') {
			copy.re = real;
			copy.im = imaginary;
		}
		else {
			in.setstate(std::ios_base::failbit);
		}
	}
	return in;
}