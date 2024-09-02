//
// Created by stellaura on 01/09/24.
//
#include "multiplicative_inverse.h"
#include <catch2/catch_all.hpp>
#include <iostream>

TEST_CASE("extended gcd") {
    int a = 10;
    int b = 7;
    int m, n;
    _implementation::ex_gcd(a, b, m, n);
    REQUIRE(a * m + b * n == 1);

    a = 17;
    b = 2133;
    _implementation::ex_gcd(a, b, m, n);
    REQUIRE(a * m + b * n == 1);

    a = 8;
    b = 2;
    _implementation::ex_gcd(a, b, m, n);
    REQUIRE(a * m + b * n == 2);
}

TEST_CASE("multiplicative inverse") {
    int a, b, expected;

    a = 10;
    b = 7;
    REQUIRE(multiplicative_inverse::extended_gcd(a, b) * b % a == 1);

    a = 15;
    b = 4;
    REQUIRE(multiplicative_inverse::extended_gcd(a, b) * b % a == 1);
}

TEST_CASE("quick pow") {
    int a, b, expected;

    a = 11;
    b = 7;
    REQUIRE(multiplicative_inverse::extended_gcd(a, b) * b % a == 1);

    a = 17;
    b = 4;
    REQUIRE(multiplicative_inverse::extended_gcd(a, b) * b % a == 1);
}
