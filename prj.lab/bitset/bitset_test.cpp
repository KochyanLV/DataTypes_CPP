#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <bitset/bitset.h>
#include <doctest/doctest.h>
#include <sstream>
#include <string>

TEST_CASE("[bitset] - bitset ctor") {
	CHECK(Bitset("11111") == Bitset(5, true));
	CHECK(Bitset("0000000") == (Bitset(7, true) << 7));
	CHECK(Bitset("0000000") == (Bitset(7, true) >> 7));
	CHECK_THROWS(Bitset(-1) == Bitset(0));
	CHECK_THROWS(Bitset("123321321123"));
}

TEST_CASE("[bitset] - operators") {
	CHECK(Bitset(123) != Bitset(122));
	CHECK(Bitset(123) == Bitset(123));
	Bitset a = Bitset("101010101");
	Bitset b;
	b = a;
	CHECK(a == b);
	a.resize(15, true);
	CHECK(a != b);
	CHECK_THROWS(a ^= b);
	CHECK_THROWS(a |= b);
	CHECK_THROWS(a &= b);
	a = Bitset("10101010101");
	b = Bitset("01010101010");
	CHECK(a == ~b);
	Bitset c = Bitset("01010101010");
	CHECK(b.size() == 11);
	CHECK((a & b) == Bitset("00000000000"));
	CHECK((a | b) == Bitset("11111111111"));
	CHECK((a ^ b) == Bitset("11111111111"));
	CHECK((b ^ c) == Bitset("00000000000"));
	a >>= 2;
	CHECK(a == Bitset("00101010101"));
	a <<= 2;
	CHECK(a == Bitset("10101010100"));
	a >>= 1;
	CHECK(a == Bitset("01010101010"));
	a >>= 0;
	a <<= 0;
	CHECK_THROWS(a >>= -1);
	CHECK_THROWS(a <<= -1);
	CHECK_THROWS(a << -1);
	CHECK_THROWS(a >> -1);
	CHECK_THROWS(Bitset(1)[5]);
	CHECK_THROWS(Bitset(1)[1]);
}

TEST_CASE("[bitset] - input_output") {
	std::stringstream input("111011101100011");
	Bitset a;
	input >> a;
	CHECK(a == Bitset("111011101100011"));
}
TEST_CASE("extra tests") {
	Bitset a(24, 1);
	CHECK(a == Bitset("111111111111111111111111"));
	a <<= 2;
	CHECK(a == Bitset("111111111111111111111100"));
	a >>= 2;
	CHECK(a == Bitset("001111111111111111111111"));
	CHECK_THROWS_AS(Bitset(-3), std::invalid_argument);
	CHECK_THROWS_AS(Bitset(0) &= Bitset(1), std::logic_error);
	CHECK_THROWS(Bitset(3)[-1]);
	Bitset b(24, 1);
	std::stringstream sstream("");
	sstream << b;
	CHECK(sstream.str() == std::string("111111111111111111111111"));
	bool bool_buff = a[22];
	CHECK_FALSE(bool_buff);
	a[22] = false;
	CHECK(~a[22]);
}