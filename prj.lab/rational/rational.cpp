#include <iostream>
#include <rational/rational.h>
int find_gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return find_gcd(a % b, b);
    return find_gcd(a, b % a);
}
int find_scm(int a, int b) {
    return a * b / find_gcd(a, b);
}
void reduction_v2(int &a, int &b) {
    int nod = find_gcd(std::abs(a), std::abs(b));
    a /= nod;
    b /= nod;
    if (b < 0) { a *= -1; b *= -1; }
}
Rational Rational::operator = (const Rational& copy) {
	ch = copy.ch;
	zn = copy.zn;
	return *this;
}
Rational Rational::operator += (const Rational& copy) {
    int nok = find_scm(zn, copy.zn);
    ch = ch * (nok / zn) + copy.ch * (nok / copy.zn);
    zn = nok;
    reduction_v2(ch, zn);
    return *this;
}
Rational Rational::operator -= (const Rational& copy) {
    int nok = find_scm(zn, copy.zn);
    ch = ch * (nok / zn) - copy.ch * (nok / copy.zn);
    zn = nok;
    reduction_v2(ch, zn);
    return *this;
}
Rational Rational::operator *= (const Rational& copy) {
    ch *= copy.ch;
    zn *= copy.zn;
    reduction_v2(ch, zn);
    return *this;
}
Rational Rational::operator /= (const Rational& copy) {
    if (copy.ch == 0) {
        throw  "Division error by zero!";
    }
    ch *= copy.zn;
    zn *= copy.ch;
    reduction_v2(ch, zn);
    return *this;
}
Rational Rational::operator + (const Rational& copy) const {
    Rational temp(*this);
    return temp += copy;
}
Rational Rational::operator - (const Rational& copy) const {
    Rational temp(*this);
    return temp -= copy;
}
Rational Rational::operator * (const Rational& copy) const {
    Rational temp(*this);
    return temp *= copy;
}
Rational Rational::operator / (const Rational& copy) const {
    Rational temp(*this);
    return temp /= copy;
}
bool Rational::operator == (const Rational& copy) const {
    return (ch == copy.ch && zn == copy.zn);
}
bool Rational::operator != (const Rational& copy) const {
    return !(ch == copy.ch && zn == copy.zn);
}
bool Rational::operator > (const Rational& copy) const {
    double a, b;
    a = double(ch) / double(zn);
    b = double(copy.ch) / double(copy.zn);
    return (a > b);
}
bool Rational::operator < (const Rational& copy) const {
    double a, b;
    a = double(ch) / double(zn);
    b = double(copy.ch) / double(copy.zn);
    return (a < b);
}
Rational Rational::operator -() const {
    Rational copy = *this;
    copy *= Rational{ -1, 1 };
    return copy;
}
std::ostream& operator << (std::ostream& out, Rational& copy) {
    out << copy.ch << "/" << copy.zn;
    return out;
}
std::istream& operator >> (std::istream& in, Rational& copy){
    in >> copy.ch;
    char separator(' ');
    in >> std::noskipws;
    if (in.peek() != '/') {
        in.setstate(std::ios_base::failbit);
    }
    in >> separator;
    if (in.peek() == '-' || in.peek() == ' ') {
        in.setstate(std::ios_base::failbit);
    }
    in >> copy.zn >> std::skipws;
    if (copy.zn == 0) {
        throw(std::exception("Division error by zero!"));
    }
    reduction_v2(copy.ch, copy.zn);
    return in;
}