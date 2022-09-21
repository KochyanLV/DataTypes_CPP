#include <iostream>
#pragma once
#ifndef RATIONAL_RATIONAL_H_20220309
#define RATIONAL_RATIONAL_H_20220309
int find_gcd(int a, int b);
int find_scm(int a, int b);
class Rational {
public:
	int ch, zn;
	Rational() { ch = 0; zn = 1; }
	Rational(const int chisl) { ch = chisl; zn = 1; }
	Rational(const int chisl, const int znam) {
		ch = chisl;
		zn = znam;
		if (zn == 0) throw "Error division by zero!";
		reduction();
	}
	Rational(const Rational& copy) { ch = copy.ch; zn = copy.zn; }
	Rational operator = (const Rational& copy);
	Rational operator + (const Rational& copy) const;
	Rational operator - (const Rational& copy) const;
	Rational operator * (const Rational& copy) const;
	Rational operator / (const Rational& copy) const;
	bool operator == (const Rational& copy) const;
	bool operator != (const Rational& copy) const;
	bool operator > (const Rational& copy) const;
	bool operator < (const Rational& copy) const;
	Rational operator += (const Rational& copy);
	Rational operator -= (const Rational& copy);
	Rational operator *= (const Rational& copy);
	Rational operator /= (const Rational& copy);
	Rational operator - () const;
	void reduction() {
		int nod = find_gcd(ch, zn);
		ch /= nod;
		zn /= nod;
		if (zn < 0) { ch *= -1; zn *= -1; }
	}
};
std::ostream& operator << (std::ostream& out, Rational& copy);
std::istream& operator >> (std::istream& in, Rational& copy);
#endif