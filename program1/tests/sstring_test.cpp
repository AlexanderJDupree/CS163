/*
File: sstring_test.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include <catch.hpp>
#include "sstring.h"

TEST_CASE("Constructing strings", "[SString], [constructos]")
{
    SECTION("Default construction")
    {
        SString string;

        REQUIRE(string.empty());

        bool assert = string.capacity() == 50;
        REQUIRE(assert);
    }
    SECTION("C-String construction")
    {
        SString string("Hello");

        bool assert = string == "Hello";
        REQUIRE(assert);

        assert = string.capacity() == 50;
        REQUIRE(assert);
    }
    SECTION("C-string construction with inadequate buffer")
    {
        SString string("Hello World", 6);

        bool assert = string == "Hello";
        REQUIRE(assert);
    }
    SECTION("Copy construction")
    {
        SString origin("Hello World");
        SString copy(origin);

        bool assert = origin == copy;
        REQUIRE(assert);

        assert = copy.length() == 11;
        REQUIRE(assert);
    }

}

TEST_CASE("Using copy-assignent operator for SString", "[SString], [operators], [copy]")
{
    SECTION("empty string and a populated string")
    {
        SString origin("Hello World");
        SString copy;

        bool assert = (copy = origin) == origin;

        REQUIRE(assert);
    }
    SECTION("two populated string")
    {
        SString origin("Hello World");
        SString copy("Not hello world");

        bool assert = (copy = origin) == origin;

        REQUIRE(assert);
    }
    SECTION("two empty strings")
    {
        SString origin;
        SString copy;

        bool assert = (copy = origin) == origin;

        REQUIRE(assert);
    }
}

TEST_CASE("Using comparison operators", "[SString], [operator]")
{
    SECTION("different strings")
    {
        SString aardvark("aardvark");
        SString apple("apple");

        bool assert = aardvark < apple;

        REQUIRE(assert);
    }
    SECTION("compare inequality")
    {
        SString due("Due");
        SString data("Data Structure");

        bool assert = due != data;
        REQUIRE(assert);
    }
    SECTION("Compare equality of null terminated default strings")
    {
        SString lhs("");
        SString rhs("");

        bool assert = lhs == rhs;
        REQUIRE(assert);
    }
    SECTION("Compare equality of default strings")
    {
        SString lhs;
        SString rhs;

        bool assert = lhs == rhs;
        REQUIRE(assert);
    }
}
