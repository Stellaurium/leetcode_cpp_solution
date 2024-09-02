//
// Created by stellaura on 01/09/24.
//
#include "rolling_hash.h"
#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("Rolling Hash Test") {
    std::string s = "hello world";
    RollingHash<char> rh{256, 93563};


    rh.push_back('h');
    REQUIRE(rh.get_hash() == 'h');

    rh.push_back('e');
    REQUIRE(rh.get_hash() == ('e' << 8) + 'h');

    rh.pop_front('h');
    REQUIRE(rh.get_hash() == 'e');

    rh.pop_front('e');
    REQUIRE(rh.get_hash() == 0);
}

TEST_CASE("RollingHashWithString Test"){
    std::string s = "hello world";
    RollingHashWithString<char> rh{s, 256, 93563};
    RollingHashWithString<char> rh2{s, 256, 93563};

    REQUIRE(rh.get_hash() == 0);

    rh.back_go_forward();
    auto temp = rh.get_hash();
    rh.back_go_backward();
    REQUIRE(rh.get_hash() == 0);

    rh.back_go_forward();
    rh.back_go_forward();
    rh.back_go_backward();
    REQUIRE(rh.get_hash() == temp);

    rh.back_go_forward();
    rh.front_go_forward();

    rh2.back_go_forward();
    rh2.back_go_forward();
    rh2.front_go_forward();
    REQUIRE(rh.get_hash() == rh2.get_hash());
}