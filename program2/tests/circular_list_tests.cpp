/*
File: circular_list_tests.cpp

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include <iostream>
#include "catch.hpp"
#include "circular_list.h"

TEST_CASE("Constructing circular lists", "[circular_list], [constructor]")
{
    SECTION("Default construction")
    {
       circular_linked_list<int> list; 

       REQUIRE(list.empty());
    }
    SECTION("Ranged based construction")
    {
        int nums[] = { 1, 2, 3, 4, 5 };

        circular_linked_list<int> list(nums, nums + 5);

        REQUIRE(list.size() == 5);

        int i = 0;
        circular_linked_list<int>::const_iterator it = list.begin();

        do {
            REQUIRE(*it == ++i);
            ++it;
        } while( it != list.end());
    }
    SECTION("Copy construction")
    {
        int nums[] = { 1, 2, 3, 4, 5 };

        circular_linked_list<int> origin(nums, nums + 5);
        circular_linked_list<int> copy(origin);

        REQUIRE(origin == copy);
    }
}

TEST_CASE("Pushing to the back of the list", "[circular_list], [push_back]")
{
    circular_linked_list<int> list;

    SECTION("Pushing to an empty list")
    {
        list.push_back(1);

        REQUIRE(*list.begin() == 1);
    }
    SECTION("Pushing multiple elements to the list")
    {
        list.push_back(2).push_back(3).push_back(4);

        int i = 1;
        circular_linked_list<int>::const_iterator it = list.begin();

        do {
            CHECK(*it == ++i);
            ++it;
        } while( it != list.end());
    }
}

TEST_CASE("Popping elements from the front of the list", "[circular_list], [pop_front]")
{

    char letters[] = { 'a', 'b', 'c', 'd', 'e' };

    circular_linked_list<char> list(letters, letters + 5);

    circular_linked_list<char> one_item(letters, letters + 1);

    circular_linked_list<int> empty;


    SECTION("pop an empty list")
    {
        REQUIRE(empty.size() == empty.pop_front().size());
    }

    SECTION("Pop a populated list")
    {
        REQUIRE(list.pop_front().size() == 4);
        REQUIRE(*list.begin() == 'b');
    }
    SECTION("Catch a popped variable")
    {
        char letter;

        REQUIRE(list.pop_front(letter) == 'a');
    }
    SECTION("Pop a single item list")
    {
        REQUIRE(one_item.pop_front().empty());
    }
}

TEST_CASE("Clearing a list", "[circular_list], [clear]")
{
    int nums[] = { 1, 2, 3, 4, 5 };

    circular_linked_list<int> list(nums, nums + 5);

    circular_linked_list<int> empty;

    SECTION("A populated list")
    {
        REQUIRE(list.clear().empty());
    }
    SECTION("An empty list")
    {
        REQUIRE(empty.clear().empty());
    }
}

struct is_seven
{
    bool operator()(const int& num)
    {
        return num == 7;
    }
};

TEST_CASE("Removing an item with a functor predicate", "[circular_list], [remove_if]")
{
    int nums[] = { 1, 2, 7, 3, 4, 5};

    circular_linked_list<int> has_target(nums, nums + 6);

    circular_linked_list<int> no_target(nums, nums + 2);
    
    circular_linked_list<int> only_target;

    circular_linked_list<int> empty;

    SECTION("Target is in the list")
    {
        REQUIRE(has_target.remove_if(is_seven()));
        REQUIRE(has_target.size() == 5);

    }
    SECTION("Target is the only element in the list")
    {
        REQUIRE(only_target.push_back(7).remove_if(is_seven()));
        REQUIRE(only_target.size() == 0);
    }
    SECTION("Target is not in the list")
    {
        REQUIRE_FALSE(no_target.remove_if(is_seven()));
        REQUIRE(no_target.size() == 2);
    }
    SECTION("Empty list")
    {
        REQUIRE(empty.empty());
    }
}

TEST_CASE("Swapping lists", "[circular_list], [swap]")
{
    int nums[] = { 1, 2, 3, 4, 5 };

    circular_linked_list<int> list1(nums, nums + 5);

    circular_linked_list<int> list2(nums, nums + 2);

    SECTION("Swap populated lists")
    {

        circular_linked_list<int>::swap(list1, list2);

        REQUIRE(list1.size() == 2);
        REQUIRE(list2.size() == 5);

        int i = 0;
        circular_linked_list<int>::const_iterator it = list2.begin();
        do
        {
            REQUIRE(*it == ++i);
            ++it;
        } while (it != list2.end());
    }

}

TEST_CASE("Using the copy assignment operator")
{
    int nums[] = { 1, 2, 3, 4, 5 };

    circular_linked_list<int> list1(nums, nums + 5);

    circular_linked_list<int> list2(nums, nums + 2);

    SECTION("Two populated lists")
    {
        REQUIRE((list1 = list2) == list2);
    }
}
