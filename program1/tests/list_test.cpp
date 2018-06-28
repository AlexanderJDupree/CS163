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
}

TEST_CASE("Using clear to erase the list", "[list], [clear], [destructor]")
{
    SECTION("An empty list")
    {
        Sorted_List<char> list;

        list.clear();

        REQUIRE(list.empty());
    }

}

TEST_CASE("Using push_front to modify the list", "[list], [modifiers], [push_front]")
{
    SECTION("An empty list")
    {
        Sorted_List<int> list;

        list.push_front(3);
        list.push_front(2);
        list.push_front(1);

        int i = 1;
        for(Sorted_List<int>::iterator it = list.begin(); it != list.end(); ++it)
        {
            /* 
            C++ 98 compliant version of catch framework has issues evaluating
            dereferenced iterators, so we create our own evaluator for the assertions
            */
            bool assert = *it == i++;
            REQUIRE(assert);
        }
    }
}


TEST_CASE("Using insert to modify the list", "[list], [modifiers], [insert]")
{
    SECTION("An empty list")
    {
        Sorted_List<char> list;
        

        list.insert(list.begin(), 'A');

        bool assert = *list.begin() == 'A';
        REQUIRE(assert);
    }
}
