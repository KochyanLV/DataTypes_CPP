#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <bitsett/bitsett.h>
#include <doctest/doctest.h>
#include <sstream>
#include <string>

TEST_CASE_TEMPLATE("[BitsetT] - BitsetT ctor", T, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t) {
	CHECK(BitsetT<T>("11111") == BitsetT<T>(5, true));
	CHECK(BitsetT<T>("0000000") == (BitsetT<T>(7, true) << 7));
	CHECK(BitsetT<T>("0000000") == (BitsetT<T>(7, true) >> 7));
	CHECK_THROWS(BitsetT<T>(-1) == BitsetT<T>(0));
	CHECK_THROWS(BitsetT<T>("123321321123"));
}

TEST_CASE_TEMPLATE("[BitsetT] - operators", T, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t) {
	CHECK(BitsetT<T>(123) != BitsetT<T>(122));
	CHECK(BitsetT<T>(123) == BitsetT<T>(123));
	BitsetT<T> a = BitsetT<T>("101010101");
	BitsetT<T> b;
	b = a;
	CHECK(a == b);
	a.resize(15, true);
	CHECK(a != b);
	CHECK_THROWS(a ^= b);
	CHECK_THROWS(a |= b);
	CHECK_THROWS(a &= b);
	a = BitsetT<T>("10101010101");
	b = BitsetT<T>("01010101010");
	CHECK(a == ~b);
	BitsetT<T> c = BitsetT<T>("01010101010");
	CHECK(b.size() == 11);
	CHECK((a & b) == BitsetT<T>("00000000000"));
	CHECK((a | b) == BitsetT<T>("11111111111"));
	CHECK((a ^ b) == BitsetT<T>("11111111111"));
	CHECK((b ^ c) == BitsetT<T>("00000000000"));
	a >>= 2;
	CHECK(a == BitsetT<T>("00101010101"));
	a <<= 2;
	CHECK(a == BitsetT<T>("10101010100"));
	a >>= 1;
	CHECK(a == BitsetT<T>("01010101010"));
	a >>= 0;
	a <<= 0;
	CHECK_THROWS(a >>= -1);
	CHECK_THROWS(a <<= -1);
	CHECK_THROWS(a << -1);
	CHECK_THROWS(a >> -1);
	CHECK_THROWS(BitsetT<T>(1)[5]);
	CHECK_THROWS(BitsetT<T>(1)[1]);
}

TEST_CASE_TEMPLATE("[BitsetT] - input_output", T, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t) {
	std::stringstream input("111011101100011");
	BitsetT<T> a;
	input >> a;
	CHECK(a == BitsetT<T>("111011101100011"));
}

TEST_CASE_TEMPLATE("extra tests", T, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t) {
	BitsetT<T> a(24, 1);
	CHECK(a == BitsetT<T>("111111111111111111111111"));
	a <<= 2;
	CHECK(a == BitsetT<T>("111111111111111111111100"));
	a >>= 2;
	CHECK(a == BitsetT<T>("001111111111111111111111"));
	CHECK_THROWS_AS(BitsetT<T>(-3), std::invalid_argument);
	CHECK_THROWS_AS(BitsetT<T>(0) &= BitsetT<T>(1), std::logic_error);
	CHECK_THROWS(BitsetT<T>(3)[-1]);
	BitsetT<T> b(24, 1);
	std::stringstream sstream("");
	sstream << b;
	CHECK(sstream.str() == std::string("111111111111111111111111"));
	bool bool_buff = a[22];
	CHECK_FALSE(bool_buff);
	a[22] = false;
	CHECK(~a[22]);
}