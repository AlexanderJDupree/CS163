/*
File: hash_table_tests.cpp

Brief: Unit tests for the hash_table class

Author: Alexander Dupree

Class: CS163

Assignment: program3

Date: 07/27/2018
*/

#include "catch.hpp"
#include "hash_table.h"
#include "sstring.h"

template <>
struct hash<SString>
{
    unsigned long operator()(const char* key) const
    {
        unsigned long hash = (*(const unsigned long*)key) << 2;
        
        return ((hash *= 7109) + 9743);
    }
};

TEST_CASE("Hashing c-string", "[hasher], [cstring]")
{
    SECTION("Two different cstrings")
    {
        const char* first = "First";
        const char* second = "Second";
        
        hash<const char*> hasher;

        REQUIRE(hasher(first) != hasher(second));
    }
    SECTION("Two matching cstrings")
    {
        const char* first = "First";
        const char* second = "First";
        
        hash<const char*> hasher;

        REQUIRE(hasher(first) == hasher(second));
    }
    SECTION("Hashing custom string objects")
    {
        const SString first = "First";
        const SString second = "Second";

        hash<SString> hasher;

        REQUIRE(hasher(first) != hasher(second));
    }
    SECTION("Two matching string objects")
    {
        const SString first = "First";
        const SString second = "First";

        hash<SString> hasher;

        REQUIRE(hasher(first) == hasher(second));
    }
    SECTION("Two matching strings of different types")
    {
        const SString first = "First";
        const char* second = "First";

        hash<SString> hasher;


        REQUIRE(hasher(first) == hasher(SString(second)));
    }
    SECTION("Hashing matching floats")
    {
        const float pi = 3.1456;
        const float copy = pi;

        hash<float> hasher;
        REQUIRE(hasher(pi) == hasher(copy));
    }
}

TEST_CASE("Constructing Hash Tables", "[hash_table], [constructors]")
{
    SECTION("Default Construction")
    {
        hash_table<char, int> table;

        REQUIRE(table.empty());
        REQUIRE(table.size() == 0);
    }
    SECTION("Specify table size on construction")
    {
        hash_table<const char*, int> table(7);

        REQUIRE(table.empty());
        REQUIRE(table.buckets() == 7);
    }
}
