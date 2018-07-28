/*
File: hash_table_tests.cpp

Brief: Unit tests for the hash_table class

Author: Alexander Dupree

Class: CS163

Assignment: program3

Date: 07/27/2018
*/

#include "catch.hpp"

TEST_CASE("Constructing Hash Tables", "[hash_table], [constructors]")
{
    SECTION("Default Construction")
    {
        hash_table<char, int> table;

        REQUIRE(table.empty());
    }
}
