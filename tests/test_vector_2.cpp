#include "catch2/catch.hpp"
#include "array/vector.hpp"
#include <utility>

using dsac::array::Vector;


TEST_CASE("copy constructor") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int> copy(v);

    REQUIRE(copy.size() == 3);
    REQUIRE(copy.capacity() == v.capacity());
    REQUIRE(copy[0] == 10);
    REQUIRE(copy[1] == 20);
    REQUIRE(copy[2] == 30);

    // changing copy should not change original
    copy[0] = 50;

    REQUIRE(copy[0] == 50);
    REQUIRE(v[0] == 10);
}


TEST_CASE("copy assign") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);

    Vector<int> copy;
    copy.push_back(100);

    copy = v;

    REQUIRE(copy.size() == 2);
    REQUIRE(copy[0] == 5);
    REQUIRE(copy[1] == 10);

    copy[1] = 25;

    REQUIRE(v[1] == 10);
}


TEST_CASE("self copy assign") {
    Vector<int> v;
    v.push_back(4);
    v.push_back(8);

    v = v;

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 4);
    REQUIRE(v[1] == 8);
}


TEST_CASE("move constructor") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    Vector<int> moved(std::move(v));

    REQUIRE(moved.size() == 2);
    REQUIRE(moved[0] == 10);
    REQUIRE(moved[1] == 20);

    // original should now be empty
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}


TEST_CASE("move assign") {
    Vector<int> v;
    v.push_back(3);
    v.push_back(6);

    Vector<int> moved;
    moved.push_back(100);

    moved = std::move(v);

    REQUIRE(moved.size() == 2);
    REQUIRE(moved[0] == 3);
    REQUIRE(moved[1] == 6);

    REQUIRE(v.empty());
    REQUIRE(v.capacity() == 0);
}


TEST_CASE("empty copy and move") {
    Vector<int> v;

    Vector<int> copy(v);

    REQUIRE(copy.empty());
    REQUIRE(copy.size() == 0);

    Vector<int> moved(std::move(copy));

    REQUIRE(moved.empty());
    REQUIRE(copy.empty());
}


TEST_CASE("iterator dereference") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::iterator it = v.begin();

    REQUIRE(*it == 10);

    *it = 50;

    REQUIRE(v[0] == 50);
}


TEST_CASE("iterator increment") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    auto it = v.begin();

    REQUIRE(*it == 5);

    ++it;
    REQUIRE(*it == 10);

    it++;
    REQUIRE(*it == 15);

    ++it;
    REQUIRE(it == v.end());
}


TEST_CASE("iterator decrement") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it = v.end();

    --it;
    REQUIRE(*it == 3);

    it--;
}