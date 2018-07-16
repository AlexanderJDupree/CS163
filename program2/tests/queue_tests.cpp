/*
File: queue_tests.cpp

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "catch.hpp"
#include "queue.h"

TEST_CASE("Constructing queue", "[queue], [constructor]")
{
    SECTION("Default construction")
    {
        Queue<int> queue;

        REQUIRE(queue.empty());
    }
}

TEST_CASE("Adding items to the queue", "[queue], []")
{

}
