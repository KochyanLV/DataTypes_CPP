#include <complex/complex.h>
#include <sstream>
void Test(Complex a, Complex b) {
	Complex ans1(6, 14);
	Complex ans2(4, -4);
	Complex ans3(-40, 50);
	Complex ans4(3, 2);
	Complex ans5(6, 14);
	Complex ans6(4, -4);
	Complex ans7(-40, 50);
	bool ans9 = 1;
	Complex ans10(-5, -5);
	if ((a + b) == ans1) {
		std::cout << "Test 1 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 1" << std::endl;
	}
	if ((a - b) == ans2) {
		std::cout << "Test 2 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 2" << std::endl;
	}
	if ((a * b) == ans3) {
		std::cout << "Test 3 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 3" << std::endl;
	}
	if ((Complex(1, 5) / Complex(1, 1)) == ans4) {
		std::cout << "Test 4 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 4" << std::endl;
	}
	Complex c = a, d = a, e = a, f = a;
	c += b;
	d -= b;
	e *= b;
	f /= b;
	if (c == ans5) {
		std::cout << "Test 5 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 5" << std::endl;
	}
	if (d == ans6) {
		std::cout << "Test 6 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 6" << std::endl;
	}
	if (e == ans7) {
		std::cout << "Test 7 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 7" << std::endl;
	}
	if ((a != b) == ans9) {
		std::cout << "Test 9 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 9" << std::endl;
	}
	if (-a == ans10) {
		std::cout << "Test 10 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 10" << std::endl;
	}
	std::stringstream potok("{5,5}  {1,9}");
	Complex test;
	potok >> test;
	if (test == a) {
		std::cout << "Input test is correct" << std::endl;
	}
	else {
		std::cout << "Input mistake" << std::endl;
	}
	potok >> test;
	if (test == b) {
		std::cout << "Input test is correct" << std::endl;
	}
	else {
		std::cout << "Input mistake" << std::endl;
	}
	std::stringstream stream;
	Complex q = Complex(2, 5);
	stream << q;
	std::string str;
	stream >> str;
	if (str == "{2,5}") {
		std::cout << "Output test is correct" << std::endl;
	}
	else {
		std::cout << "Output mistake" << std::endl;
	}
	int p = 5;
	Complex ans20(10, 5);
	Complex ans21(0, 5);
	Complex ans22(25, 25);
	Complex ans23(1, 1);
	Complex p1 = a, p2 = a, p3 = a, p4 = a;
	p1 += p;
	p2 -= p;
	p3 *= p;
	p4 /= p;
	if ((a + p) == ans20) {
		std::cout << "Test 12 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 12" << std::endl;
	}
	if ((a - p) == ans21) {
		std::cout << "Test 13 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 13" << std::endl;
	}
	if ((a * p) == ans22) {
		std::cout << "Test 14 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 14" << std::endl;
	}
	if ((a / p) == ans23) {
		std::cout << "Test 15 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 15" << std::endl;
	}
	if (p1 == ans20) {
		std::cout << "Test 16 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 16" << std::endl;
	}
	if (p2 == ans21) {
		std::cout << "Test 17 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 17" << std::endl;
	}
	if (p3 == ans22) {
		std::cout << "Test 18 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 18" << std::endl;
	}
	if (p4 == ans23) {
		std::cout << "Test 19 is correct" << std::endl;
	}
	else {
		std::cout << "Mistake on test 19" << std::endl;
	}
}
int main() {
	Complex a(5, 5);
	Complex b(1, 9);
	Test(a, b);
	return 0;
}