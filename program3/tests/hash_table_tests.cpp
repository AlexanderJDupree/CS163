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
    SECTION("Range based construction")
    {
        SString keys[] = { "Bob", "Alice", "Jack", "Jill" };
        int values[] = { 1, 2, 3, 4 };
        
        hash_table<SString, int> table(keys, keys + 4, values, values +4);

        REQUIRE(table.size() == 4);
    }
    SECTION("Ranged based construction on mismatched arrays")
    {
        SString keys[] = { "Bob", "Alice" };
        int values[] = { 1, 2, 3, 4 };

        hash_table<SString, int> table(keys, keys + 2, values, values +4);
        REQUIRE(table.size() == 2);
    }
}

TEST_CASE("Inserting elements into the hash table", "[hash_table], [modifiers], [insert]")
{
    SECTION("An empty hash table")
    {
        hash_table<SString, int> table;

        REQUIRE(table.insert("Hello", 7).size() == 1);
        REQUIRE_FALSE(table.empty());
    }
    SECTION("Inserting multiple elements into a hash table")
    {
        hash_table<SString, int> table;

        table.insert("Bob", 1).insert("Alice", 2).insert("John", 3);
        REQUIRE(table.size() == 3);
    }
}

TEST_CASE("Iterating through a hash table", "[hash_table], [iterators]")
{
    SECTION("An empty hash table")
    {
        const hash_table<SString, int> table;

        REQUIRE(table.begin() == table.end());
    }
    SECTION("Dereferencing an empty iterator throws")
    {
        const hash_table<SString, int> table;

        REQUIRE_THROWS(*table.begin());
    }
    SECTION("A populated hash table")
    {
        SString keys[] = { "Bob", "Bob", "Bob", "Bob" };
        int values[] = { 1, 1, 1, 1 };
        
        const hash_table<SString, int> table(keys, keys + 4, values, values +4);

        int i = 0;
        hash_table<SString, int>::const_iterator it;
        for(it = table.begin(); it != table.end(); ++it)
        {
            REQUIRE(it.key() == keys[i]);
            REQUIRE(it.value() == values[i++]);
        }
        REQUIRE(i == 4);
    }
    SECTION("Modifying the value of each element in a hash table")
    {
        SString keys[] = { "Bob", "Bob", "Bob", "Bob" };
        int values[] = { 1, 1, 1, 1 };
        
        hash_table<SString, int> table(keys, keys + 4, values, values +4);

        int i = 0;
        hash_table<SString, int>::iterator it;
        for(it = table.begin(); it != table.end(); ++it)
        {
            REQUIRE(it.key() == keys[i++]);
            REQUIRE(++it.value() == 2);
        }
    }
}


TEST_CASE("Clearing the contents of the hash table", "[hash_table], [modifiers], [clear]")
{
    SECTION("An empty hash table")
    {
        hash_table<float, int> table;

        REQUIRE(table.clear().empty());
    }
    SECTION("A populated hash table")
    {
        SString keys[] = { "Bob", "Alice", "Jack", "Jill" };
        int values[] = { 1, 2, 3, 4 };
        
        hash_table<SString, int> table(keys, keys + 4, values, values +4);

        REQUIRE(table.clear().empty());
    }
}
