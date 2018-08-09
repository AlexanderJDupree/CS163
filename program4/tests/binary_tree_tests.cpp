/*
File: binary_tree_test.cpp

Brief: Unit tests for the binary search tree data structure

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/24/2018
*/

#include <iostream>
#include "catch.hpp"
#include "binary_search_tree.h"

TEST_CASE("Constructing binary search trees", "[bst], [constructors]")
{
    SECTION("Default Construction")
    {
        binary_tree<int, char> tree;

        REQUIRE(tree.empty());
        REQUIRE(tree.height() == 0);
    }
    SECTION("Range based Construction")
    {
        int keys[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
        char vals[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        binary_tree<int, char> tree(keys, keys + 8, vals, vals + 8);

        REQUIRE(tree.size() == 8);
        REQUIRE(tree.height() == 4);

        int i = 0;
        binary_tree<int, char>::const_iterator it;
        for(it = tree.begin(); it != tree.end(); ++it)
        {
            REQUIRE(it.key() == ++i);
        }
    }
    SECTION("Copy construction")
    {
        int keys[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
        char vals[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        binary_tree<int, char> origin(keys, keys + 8, vals, vals + 8);


        binary_tree<int, char> copy(origin);
        
        REQUIRE(copy.size() == origin.size());

        REQUIRE(copy == origin);
    }
}

TEST_CASE("Inserting into binary search tree", "[bst], [insert]")
{
    binary_tree<int, char> tree;

    SECTION("Inserting one item into an empty tree")
    {
        REQUIRE(tree.insert(7, 'a').size() == 1);
        REQUIRE(tree.height() == 1);
        REQUIRE(tree.root() == 'a');
    }
    SECTION("Inserting multiple items into an empty tree")
    {
        tree.insert(2, 'a').insert(1, 'a').insert(3, 'b');

        REQUIRE(tree.size() == 3);
        REQUIRE(tree.height() == 2);

        int i = 0;
        binary_tree<int, char>::iterator it;
        for(it = tree.begin(); it != tree.end(); ++it)
        {
            REQUIRE(it.key() == ++i);
        }
    }
}

TEST_CASE("Finding items in a BST", "[bst], [find]")
{
    char keys[] = { 'e', 'f', 'd', 'g', 'b', 'a', 'c' };
    int vals[] = { 1, 2, 3, 4, 5, 6, 7 };
    binary_tree<char, int> tree(keys, keys + 7, vals, vals + 7);
    tree.default_object(-1);

    binary_tree<float, float> empty;
    empty.default_object(-1.0);

    SECTION("Retrieving an item from a BST")
    {
        REQUIRE(tree.find('a') == 6);
    }
    SECTION("find with an unmatched search key")
    {
        REQUIRE(tree.find('z') == -1);
    }
    SECTION("Retrieval with an item BST")
    {
        REQUIRE(empty.find(3.14) == -1.0);
    }
    SECTION("Retrieval with the [] operator")
    {
        REQUIRE(tree['d'] == 3);
    }
}

TEST_CASE("Counting the number of leaves in a BST", "[bst], [leaves]")
{
    int keys[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
    char vals[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    binary_tree<int, char> tree(keys, keys + 8, vals, vals + 8);

    binary_tree<int, char> empty;

    SECTION("Populated search tree")
    {
        REQUIRE(tree.leaves() == 3);
    }
    SECTION("An empty tree")
    {
        REQUIRE(empty.leaves() == 0);
    }

}

TEST_CASE("Clearing a BST", "[bst], [clear]")
{
    int keys[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
    char vals[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    binary_tree<int, char> tree(keys, keys + 8, vals, vals + 8);


    SECTION("A populated search tree")
    {
        REQUIRE(tree.clear().empty());
    }
}

TEST_CASE("Using the equality operators", "[bst], [equality]")
{
    int keys[] = { 4, 6, 8, 3, 5, 1, 2, 7 };
    char vals[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

    int keys2[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int vals2[] = { 'f', 'g', 'd', 'a', 'e', 'b', 'h', 'c' };
    binary_tree<int, char> lhs(keys, keys + 8, vals, vals + 8);
    binary_tree<int, char> rhs(keys2, keys2 + 8, vals2, vals2 + 8);

    binary_tree<int, char> sub_tree(keys, keys + 6, vals, vals + 6);

    SECTION("Tree's with the same contents but different shape")
    {
        REQUIRE(lhs == rhs);
    }
    SECTION("Sub tree does not mean equality")
    {
        REQUIRE(lhs != sub_tree);
    }
}

TEST_CASE("Erasing elements from a tree", "[bst], [erase]")
{
        binary_tree<int, int> empty;

    SECTION("Removing from an empty tree")
    {
        REQUIRE_FALSE(empty.erase(10));

    }

    SECTION("Removing an item that doesn't exit")
    {
        int keys[] = { 50, 25, 75, 12, 40, 33, 45, 35, 10, 16, 60, 90, 94 };
        int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        binary_tree<int, int> tree(keys, keys + 13, vals, vals + 13);


        REQUIRE_FALSE(tree.erase(-1));
    }
    SECTION("Removing a leaf")
    {
        int keys[] = { 50, 25, 75, 12, 40, 33, 45, 35, 10, 16, 60, 90, 94 };
        int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        binary_tree<int, int> tree(keys, keys + 13, vals, vals + 13);

        REQUIRE(tree.erase(10));
        REQUIRE(tree.size() == 12);
        REQUIRE(tree.leaves() == 5);
    }
    SECTION("Removing a node with only one right child")
    {
        int keys[] = { 50, 25, 75, 12, 40, 33, 45, 35, 10, 16, 60, 90, 94 };
        int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        binary_tree<int, int> tree(keys, keys + 13, vals, vals + 13);

        REQUIRE(tree.erase(90));
        REQUIRE(tree.leaves() == 6);
    }
    SECTION("Removing a node with only one left child")
    {
        int keys[] = { 50, 25, 75, 12, 40, 33, 45, 35, 10, 16, 60, 90, 1 };
        int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        binary_tree<int, int> tree(keys, keys + 13, vals, vals + 13);

        REQUIRE(tree.erase(10));
        REQUIRE(tree.leaves() == 6);
        REQUIRE((++tree.smallest()).key() == 12);

    }
    SECTION("Removing a node with two childs and a right child with no children")
    {
        int keys[] = { 50, 25, 75, 12, 40, 33, 45, 35, 10, 16, 60, 90 };
        int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        binary_tree<int, int> tree(keys, keys + 12, vals, vals + 12);

        // Inorder succesor has no children
        REQUIRE(tree.erase(40));
        REQUIRE(tree.leaves() == 5);

        // Inorder succesor has a right child
        REQUIRE(tree.erase(25));

        // Erase root
        REQUIRE(tree.erase(50));

     }
}

