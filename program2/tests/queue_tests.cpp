/*
File: queue_tests.cpp

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "catch.hpp"
#include "feature_queue.h"

TEST_CASE("Constructing queue", "[queue], [constructor]")
{
    SECTION("Default construction")
    {
        Feature_Queue queue;

        REQUIRE(queue.empty());
    }
    SECTION("Ranged based construction")
    {
        SString strings[] = { "Hey", "Okay", "Cool" };

        Feature_Queue queue(strings, strings + 3);

        SString temp;
        for(unsigned i = 0; i < 3; ++i)
        {
            REQUIRE(strings[i] == queue.dequeue(temp));
        }
    }
}

TEST_CASE("Adding items to the queue", "[queue], []")
{

}
