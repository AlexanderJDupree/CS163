/*
File: binary_tree_test.cpp

Brief: Unit tests for the binary search tree data structure

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/24/2018
*/

#include "catch.hpp"
#include "binary_search_tree.h"

TEST_CASE("Constructing binary search trees", "[bst], [constructors]")
{
    SECTION("Default Construction")
    {
        binary_tree<int> tree;

        REQUIRE(tree.empty());
        REQUIRE(tree.height() == 0);
    }
    SECTION("Range based Construction")
    {
        int nums[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
        binary_tree<int> tree(nums, nums + 8);

        REQUIRE(tree.size() == 8);
        REQUIRE(tree.height() == 4);

        int i = 0;
        binary_tree<int>::const_iterator it;
        for(it = tree.begin(); it != tree.end(); ++it)
        {
            REQUIRE(*it == ++i);
        }
    }
}

TEST_CASE("Inserting into binary search tree", "[bst], [insert]")
{
    binary_tree<int> tree;

    SECTION("Inserting one item into an empty tree")
    {
        REQUIRE(tree.insert(7).size() == 1);
        REQUIRE(tree.height() == 1);
        REQUIRE(tree.root() == 7);
    }
    SECTION("Inserting multiple items into an empty tree")
    {
        tree.insert(2).insert(1).insert(3);

        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);

        int i = 0;
        binary_tree<int>::const_iterator it;
        for(it = tree.begin(); it != tree.end(); ++it)
        {
            REQUIRE(*it == ++i);
        }
    }
}

TEST_CASE("Finding items in a BST", "[bst], [find]")
{
    char letters[] = { 'e', 'f', 'd', 'g', 'b', 'a', 'c' };
    binary_tree<char> tree(letters, letters + 7);
    tree.default_object('\0');

    binary_tree<float> empty;
    empty.default_object(-1.0);

    SECTION("Retrieving an item from a BST")
    {
        REQUIRE(tree.find('a') == 'a');
    }
    SECTION("find with an unmatched search key")
    {
        REQUIRE(tree.find('z') == '\0');
    }
    SECTION("Retrieval with an item BST")
    {
        REQUIRE(empty.find(3.14) == -1.0);
    }
}

TEST_CASE("Clearing a BST", "[bst], [clear]")
{
    char letters[] = { 'e', 'f', 'd', 'g', 'b', 'a', 'c' };
    binary_tree<char> tree(letters, letters + 7);

    SECTION("A populated search tree")
    {
        REQUIRE(tree.clear().empty());
    }

}

