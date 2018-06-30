/*
File: list_test.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include <catch.hpp>
#include "linked_list.h"

TEST_CASE("Constructing Sorted_List objects", "[list], [constructors]")
{
    SECTION("Default construction")
    {
        Sorted_List<int> list;

        REQUIRE(list.empty());
    }
    SECTION("Copy construction")
    {
        Sorted_List<int> origin;
        origin.add(1);
        origin.add(3);
        origin.add(2);

        Sorted_List<int> copy(origin);

        bool assert = origin == copy;
        REQUIRE(assert);

        assert = copy.size() == 3;
        REQUIRE(assert);
    }
}

TEST_CASE("Using clear to erase the list", "[list], [clear], [destructor]")
{
    SECTION("An empty list")
    {
        Sorted_List<char> list;

        list.clear();

        REQUIRE(list.empty());
    }
    SECTION("A populated list")
    {
        Sorted_List<char> list;

        list.add('a');
        list.add('b');
        list.add('c');

        list.clear();

        REQUIRE(list.empty());
    }

}

TEST_CASE("Using add to insert elements into sorted order", "[list], [modifiers], [add]")
{
    SECTION("An empty list")
    {
        Sorted_List<int> list;

        REQUIRE(list.add(5));
        REQUIRE(list.add(4));
        REQUIRE(list.add(8));
        REQUIRE(list.add(6));

        REQUIRE(list.add(5) == false);

        int nums[] = {4, 5, 6, 8};
        int i = 0;

        for (Sorted_List<int>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == nums[i++];
            REQUIRE(assert);
        }
    }
}

TEST_CASE("Using swap to reassign data", "[list], [swap]")
{
    SECTION("An empty list and a populated list")
    {
        Sorted_List<int> old;

        old.add(3);
        old.add(1);
        old.add(2);

        Sorted_List<int> list;

        Sorted_List<int>::swap(list, old);

        int i = 1;
        for (Sorted_List<int>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            bool assert = *it == i++;
            REQUIRE(assert);
        }
    }
    SECTION("two empty lists")
    {
        Sorted_List<int> old;
        Sorted_List<int> list;

        Sorted_List<int>::swap(list, old);

        bool assert = old == list;
        REQUIRE(assert);
    }

}

TEST_CASE("Using the copy-assignment operator", "[list], [operators], [copy-assignment]")
{
    SECTION("An empty list and a populated list")
    {
        Sorted_List<int> old;

        old.add(3);
        old.add(1);
        old.add(2);

        Sorted_List<int> list;

        list = old;

        bool assert = old == list;
        REQUIRE(assert);
    }
    SECTION("two empty lists")
    {
        Sorted_List<int> old;
        Sorted_List<int> list;

        old = list;

        bool assert = old == list;
        REQUIRE(assert);
    }
}