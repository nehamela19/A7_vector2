#include "catch2/catch.hpp"
#include "array/matrix.hpp"
#include <stdexcept>

using dsac::array::Matrix;


TEST_CASE("matrix constructor") {
    Matrix m(2, 3);

    REQUIRE(m(0, 0) == 0);
    REQUIRE(m(0, 1) == 0);
    REQUIRE(m(0, 2) == 0);
    REQUIRE(m(1, 0) == 0);
    REQUIRE(m(1, 1) == 0);
    REQUIRE(m(1, 2) == 0);
}


TEST_CASE("matrix negative dimensions") {
    REQUIRE_THROWS_AS(Matrix(-1, 3), std::out_of_range);
    REQUIRE_THROWS_AS(Matrix(3, -1), std::out_of_range);
    REQUIRE_THROWS_AS(Matrix(-2, -2), std::out_of_range);
}


TEST_CASE("matrix change elements") {
    Matrix m(2, 2);

    m(0, 0) = 5;
    m(0, 1) = 10;
    m(1, 0) = 15;
    m(1, 1) = 20;

    REQUIRE(m(0, 0) == 5);
    REQUIRE(m(0, 1) == 10);
    REQUIRE(m(1, 0) == 15);
    REQUIRE(m(1, 1) == 20);
}


TEST_CASE("matrix out of bounds") {
    Matrix m(2, 3);

    REQUIRE_THROWS_AS(m(2, 0), std::out_of_range);
    REQUIRE_THROWS_AS(m(0, 3), std::out_of_range);
    REQUIRE_THROWS_AS(m(-1, 0), std::out_of_range);
    REQUIRE_THROWS_AS(m(0, -1), std::out_of_range);
}


TEST_CASE("matrix addition") {
    Matrix a(2, 2);
    Matrix b(2, 2);

    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;

    b(0, 0) = 5;
    b(0, 1) = 6;
    b(1, 0) = 7;
    b(1, 1) = 8;

    Matrix result = a + b;

    REQUIRE(result(0, 0) == 6);
    REQUIRE(result(0, 1) == 8);
    REQUIRE(result(1, 0) == 10);
    REQUIRE(result(1, 1) == 12);
}


TEST_CASE("matrix addition different dimensions") {
    Matrix a(2, 2);
    Matrix b(3, 2);
    Matrix c(2, 3);

    REQUIRE_THROWS_AS(a + b, std::out_of_range);
    REQUIRE_THROWS_AS(a + c, std::out_of_range);
}


TEST_CASE("matrix addition with zeros") {
    Matrix a(2, 2);
    Matrix b(2, 2);

    a(0, 0) = 3;
    a(0, 1) = 6;
    a(1, 0) = 9;
    a(1, 1) = 12;

    Matrix result = a + b;

    REQUIRE(result(0, 0) == 3);
    REQUIRE(result(0, 1) == 6);
    REQUIRE(result(1, 0) == 9);
    REQUIRE(result(1, 1) == 12);
}