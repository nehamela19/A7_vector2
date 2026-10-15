#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "array/vector.hpp"

#include <stdexcept>

using dsac::array::Vector;


TEST_CASE("default vector") {
    Vector<int> v;

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}


TEST_CASE("vector with size") {
    Vector<int> v(4);

    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() == 4);

    // values should start at 0
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 0);
    REQUIRE(v[2] == 0);
    REQUIRE(v[3] == 0);
}


TEST_CASE("size negative") {
    REQUIRE_THROWS_AS(Vector<int>(-2), std::invalid_argument);
}


TEST_CASE("operator test") {
    Vector<int> v(3);

    v[0] = 5;
    v[1] = 10;
    v[2] = 15;

    REQUIRE(v[0] == 5);
    REQUIRE(v[1] == 10);
    REQUIRE(v[2] == 15);
}


TEST_CASE("at") {
    Vector<int> v(3);

    v[0] = 4;
    v[1] = 8;
    v[2] = 12;

    REQUIRE(v.at(0) == 4);
    REQUIRE(v.at(1) == 8);
    REQUIRE(v.at(2) == 12);

    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
}


TEST_CASE("front and back") {
    Vector<int> v(3);

    v[0] = 7;
    v[1] = 8;
    v[2] = 9;

    REQUIRE(v.front() == 7);
    REQUIRE(v.back() == 9);

    // make sure they are actual references
    v.front() = 20;
    v.back() = 30;

    REQUIRE(v[0] == 20);
    REQUIRE(v[2] == 30);
}


TEST_CASE("push back") {
    Vector<int> v;

    v.push_back(10);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 10);

    v.push_back(20);
    REQUIRE(v.size() == 2);
    REQUIRE(v[1] == 20);

    v.push_back(30);
    REQUIRE(v.size() == 3);
    REQUIRE(v[2] == 30);
}


TEST_CASE("increase capacity") {
    Vector<int> v;

    v.push_back(1);
    REQUIRE(v.capacity() == 1);

    v.push_back(2);
    REQUIRE(v.capacity() == 2);

    v.push_back(3);
    REQUIRE(v.capacity() == 4);
}


TEST_CASE("pop back") {
    Vector<int> v;

    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    v.pop_back();

    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 10);
}


TEST_CASE("insert") {
    Vector<int> v;

    v.push_back(10);
    v.push_back(30);

    // 30 needs to shift over
    v.insert(1, 20);

    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
    REQUIRE(v[2] == 30);
}


TEST_CASE("insert at beginning") {
    Vector<int> v;

    v.push_back(20);
    v.push_back(30);

    v.insert(0, 10);

    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
    REQUIRE(v[2] == 30);
}


TEST_CASE("erase") {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.erase(1);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 30);
}


TEST_CASE("reserve") {
    Vector<int> v;

    v.reserve(10);

    REQUIRE(v.capacity() == 10);
    REQUIRE(v.size() == 0);

    // smaller reserve should not change it
    v.reserve(5);
    REQUIRE(v.capacity() == 10);
}


TEST_CASE("reallocate keeps values") {
    Vector<int> v;

    v.push_back(3);
    v.push_back(6);
    v.push_back(9);

    v.reallocate(10);

    REQUIRE(v.capacity() == 10);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 3);
    REQUIRE(v[1] == 6);
    REQUIRE(v[2] == 9);
}


TEST_CASE("reallocate smaller") {
    Vector<int> v(4);

    REQUIRE_THROWS_AS(v.reallocate(2), std::invalid_argument);
}


TEST_CASE("shrink") {
    Vector<int> v;

    v.reserve(16);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    // size is 1/4 of capacity so it should shrink
    v.shrink();

    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() == 8);

    REQUIRE(v[0] == 1);
    REQUIRE(v[3] == 4);
}


TEST_CASE("shrink to fit") {
    Vector<int> v;

    v.reserve(20);
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    v.shrink_to_fit();

    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);
}


TEST_CASE("shrink to fit when empty") {
    Vector<int> v;

    v.reserve(10);
    v.shrink_to_fit();

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}
TEST_CASE("const functions") {
    const Vector<int> v(3);

    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);
    REQUIRE(v[0] == 0);
    REQUIRE(v.at(1) == 0);
    REQUIRE(v.front() == 0);
    REQUIRE(v.back() == 0);
}