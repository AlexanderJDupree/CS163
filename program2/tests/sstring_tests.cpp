/*
File: sstring_tests.cpp

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "catch.hpp"
#include "sstring.h"

TEST_CASE("Constructing shared strings", "[sstring], [constructors]")
{
    SECTION("Default construction")
    {
        SString str;

        REQUIRE(str.empty());
        REQUIRE(str.ref_count() == 1);
        REQUIRE(str.length() == 0);
    }
    SECTION("CString construction")
    {
        SString str("Hello");

        REQUIRE(str.length() == 5);
        REQUIRE(str == "Hello");
    }
    SECTION("Copy construction increases reference count")
    {
        SString origin("Hello");
        SString copy(origin);

        REQUIRE(copy == origin);
        REQUIRE(origin.ref_count() == 2);
    }
}

TEST_CASE("Deleting shared strings", "[sstring], [destructors]")
{
    SECTION("Deleting the original string does not effect copies")
    {
        SString* origin = new SString("Hello");
        SString first_copy (*origin);
        SString second_copy(first_copy);

        delete origin;

        REQUIRE(first_copy.ref_count() == 2);
        REQUIRE(first_copy == second_copy);
    }
}

TEST_CASE("Using the static len function on cstrings", "[sstring], [len]")
{
    const char* null_string = NULL;

    const char* empty_string = new char('\0');

    const char* str = "Hello";

    SECTION("A NULL string")
    {
        REQUIRE(SString::len(null_string) == 0);
    }
    SECTION("An empty cstring")
    {
        REQUIRE(SString::len(empty_string) == 0);
    }
    SECTION("A valid cstring")
    {
        REQUIRE(SString::len(str) == 5);
    }

    delete empty_string;
}

TEST_CASE("Iterating through a shared string", "[sstring], [iterators]")
{
    SString empty;

    SString str("abcd");

    SString copy(str);

    SECTION("An empty string")
    {
        int i = 0;
        for(SString::const_iterator it = empty.begin(); it != empty.end(); ++it)
        {
            // Loop should not iterate on an empty string
            ++i;
        }
        REQUIRE(i == 0);
    }
    SECTION("A populated string")
    {
        char letter = 'a';
        for(SString::const_iterator it = str.begin(); it != str.end(); ++it)
        {
            REQUIRE(*it == letter++);
        }
    }
    SECTION("A shared string")
    {
        char letter = 'a';
        for(SString::const_iterator it = copy.begin(); it != copy.end(); ++it)
        {
            REQUIRE(*it == letter++);
        }
    }
}

TEST_CASE("Using copy assignment operator", "[sstring], [copy-assignment]")
{
    SECTION("Assignment of an unitialized string to a populated string")
    {   
        SString uninitialized;

        SString origin("Hello");

        uninitialized = origin;

        REQUIRE(origin.ref_count() == 2);
        REQUIRE(origin == uninitialized);
    }
    SECTION("Reassignment of a popualted string")
    {
        SString first("Hello");
        SString copy(first);

        SString second("World");

        first = second;

        // The copy is now unique since the first string was reassigned
        REQUIRE(copy.ref_count() == 1);

        REQUIRE(first == second);
        REQUIRE(second.ref_count() == 2);
    }
}

TEST_CASE("Swapping strings", "[sstring], [swap]")
{
    SString empty;

    SString origin("Hello");

    SString copy(origin);
    
    SString unique("world");

    SECTION("Swapping with an empty string")
    {
        SString::swap(empty, origin);

        REQUIRE(empty.ref_count() == 2);

        REQUIRE(origin.empty());
    }
    SECTION("Swapping with a copy")
    {
        SString::swap(copy, origin);

        REQUIRE(copy.ref_count() == 2);

        REQUIRE(copy == origin);
    }
    SECTION("Swapping with a unique string")
    {
        SString::swap(copy, unique);

        REQUIRE(copy.ref_count() == 1);

        REQUIRE(unique == origin);
    }
}

TEST_CASE("Using the << operator", "[sstring], [stream extraction]")
{
    SString empty;

    SString str("Hello World!");

    SECTION("A populated string")
    {
        std::ostringstream oss;

        oss << str;

        REQUIRE(oss.str() == "Hello World!");
    }

    SECTION("An empty string")
    {
        std::ostringstream oss;

        oss << empty;

        REQUIRE(oss.str() == "");
    }
}
