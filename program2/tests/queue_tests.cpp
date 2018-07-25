/*
File: queue_tests.cpp

Brief: unit tests for the feature_queue ADT

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

TEST_CASE("Adding items to the queue", "[queue], [enqueue]")
{
    Feature_Queue queue;

    SECTION("enqueuing to an empty queue")
    {
        queue.enqueue("Hello");

        REQUIRE("Hello" == queue.front());
    }
    SECTION("enqueueing multiple items")
    {
        queue.enqueue("Hello").enqueue("World").enqueue("Bye!");

        REQUIRE("Hello" == queue.front());
        REQUIRE("Bye!" == queue.back());
    }
}

TEST_CASE("Peeking the front and back of the queue", "[queue], [front], [back]")
{
    SString strings[] = { "Hey", "Okay", "Vader", "Careless Whisper" };
    Feature_Queue populated_queue(strings, strings + 4);

    Feature_Queue empty;

    SECTION("front and back return the correct strings")
    {
        REQUIRE("Hey" == populated_queue.front());
        REQUIRE("Careless Whisper" == populated_queue.back());
    }
    SECTION("Front and back on an empty list throws")
    {
        REQUIRE_THROWS(empty.front());
        REQUIRE_THROWS(empty.back());
    }
}
