#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.h>
TEST_CASE("[rational] - Rational ctor") {
    CHECK((Rational() == Rational(0, 1)));
    CHECK((Rational(5) == Rational(5, 1)));
    CHECK((Rational(2, 4) == Rational(1, 2)));
    CHECK((Rational(-2, 4) == Rational(-1, 2)));
    CHECK((Rational(2, -4) == Rational(-1, 2)));
    CHECK((Rational(-2, -4) == Rational(1, 2)));
    CHECK((-Rational(5, 7) == Rational(-5, 7)));
}
TEST_CASE("[rational] - ariphmetic") {
    CHECK(((Rational(3, 8) += Rational(5, 12)) == Rational(19, 24)));
    CHECK(((Rational(3, 8) + Rational(6, 12)) == Rational(7, 8)));
    CHECK(((Rational(3, 8) -= Rational(5, 12)) == Rational(-1, 24)));
    CHECK(((Rational(3, 8) - Rational(6, 12))== Rational(-1, 8)));
    CHECK(((Rational(3, 8) *= Rational(5, 12)) == Rational(5, 32)));
    CHECK(((Rational(3, 8) * Rational(6, 12)) == Rational(3, 16)));
    CHECK(((Rational(3, 8) /= Rational(5, 12)) == Rational(9, 10)));
    CHECK(((Rational(3, 8) / Rational(6, 12)) == Rational(3, 4)));
}
TEST_CASE("[rational] - bool"){
    CHECK((Rational(7, 8) < Rational(6, 9)) == FALSE);
    CHECK((Rational(3, 8) < Rational(5, 12)) == TRUE);
    CHECK((Rational(2, 5) > Rational(3, 7)) == FALSE);
    CHECK((Rational(1, 1) > Rational(1, 4)) == TRUE);
    CHECK((Rational(2, -5) == Rational(2, -5)) == TRUE);
    CHECK((Rational(7, 49) == Rational(8, 48)) == FALSE);
    CHECK((Rational(2, 2) != Rational(3, 4)) == TRUE);
    CHECK((Rational(3, 3) != Rational(5, 5)) == FALSE);
}
TEST_CASE("[rational] - exceptions") {
    CHECK_THROWS(Rational(5, 0));
    CHECK_THROWS(Rational(5, 7) / Rational(0, 8));
}
TEST_CASE("[rational] - in") {
    std::stringstream potok("4/9  -1/5  7/1 0/9 -4/6 7/0 2/-0;");
    Rational test;
    potok >> test;
    CHECK((test == Rational(4, 9)));
    potok >> test;
    CHECK((test == Rational(-1, 5)));
    potok >> test;
    CHECK((test == Rational(7, 1)));
    potok >> test;
    CHECK((test == Rational(0, 9)));
    potok >> test;
    CHECK((test == Rational(-4, 6)));
    CHECK_THROWS((potok >> test));
    CHECK_THROWS((potok >> test));
}
TEST_CASE("[rational] - out") {
    std::stringstream stream;
    Rational q = Rational(3, -19);
    stream << q;
    std::string str;
    stream >> str;
    CHECK(str == "-3/19");
}