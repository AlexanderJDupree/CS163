/*
File: product_stack.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "catch.hpp"
#include "product_stack.h"

TEST_CASE("Constructing product stacks", "[stack], [constructors]")
{
    SECTION("Default Construction")
    {
        Product_Stack stack;

        REQUIRE(stack.empty());
    }
}

TEST_CASE("Pushing Products onto the stack", "[stack], [push]")
{
    Product first("Best Buy", "Acer Aspire", 150);
    Product second("Goodwill", "Macbook Air", 15000);
    Product third("Fry's", "Sony Vaio", 230);

    Product_Stack stack;

    SECTION("First push")
    {
        stack.push(first);

        REQUIRE(stack.top() == first);
    }
    SECTION("Multiple pushes")
    {
        stack.push(first).push(second).push(third);

        REQUIRE(stack.top() == third);
        REQUIRE(stack.bottom() == first);
    }
}

TEST_CASE("Clearing a stack")
{
    Product first("Best Buy", "Acer Aspire", 150);
    Product second("Goodwill", "Macbook Air", 15000);
    Product third("Fry's", "Sony Vaio", 230);

    Product_Stack stack;
    Product_Stack empty;

    stack.push(first).push(second).push(third);

    SECTION("A populated stack")
    {
        stack.clear_stack();

        REQUIRE(stack.empty());
    }
    SECTION("An empty stack")
    {
        empty.clear_stack();

        REQUIRE(empty.empty());
    }
}

TEST_CASE("Peek top and bottom of the stack")
{
    Product_Stack stack;

    SECTION("empty stack returns a default product")
    {
        REQUIRE_THROWS(stack.top());
        REQUIRE_THROWS(stack.bottom());
    }
}
