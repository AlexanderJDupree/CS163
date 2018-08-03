/*
File: sstring_tests.cpp

Brief: Extended tests for new functions for the SString class

Author: Alexander Dupree

Class: CS163

Assignment: program3

Date: 07/27/2018
*/

#include "catch.hpp"
#include "sstring.h"

TEST_CASE("Generating substrings", "[sstring], [substring]")
{
    SString string("Hello World");

    SECTION("Truncated substring")
    {
        REQUIRE(string.substring(0,4) == "Hello");
    }

    SECTION("Intermediate substring")
    {
        REQUIRE(string.substring(2, 6) == "llo W");
    }
    SECTION("Invalid substring")
    {
        REQUIRE_THROWS(string.substring(10, 3));
    }
}

TEST_CASE("Concatenating strings", "[sstring], [concatenation]")
{
    SString string("Hello");

    SECTION("lhs: SString, rhs: cstring")
    {
        REQUIRE(string + " World" == "Hello World");
    }

    SECTION("lhs: cstring, rhs: SString")
    {
        REQUIRE("World " + string == "World Hello");
    }
    SECTION("lhs: SString, rhs: SString")
    {
        REQUIRE(string + SString(" World") == "Hello World");
    }
}

TEST_CASE("Truncating strings", "[sstring], [truncate]")
{
    SString long_string("This is a really really long string");
    SString short_string("Hey");

    SECTION("Truncating long strings")
    {
        REQUIRE(long_string.truncate(16) == "This is a really");
    }
    SECTION("Truncating short strings fills the width extra width")
    {
        REQUIRE(short_string.truncate() == "Hey     ");
    }
}

TEST_CASE("Constructing fill strings", "[sstring], [constructors], [fill]")
{
    SECTION("Fill blank characters into a string")
    {
        REQUIRE(SString(4, ' ') + "Hey" == "   Hey");
    }
}

