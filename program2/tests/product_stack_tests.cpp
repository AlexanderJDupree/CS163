/*
File: product_stack.h

Brief: Unit tests for the product_stack ADT

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
        CHECK(stack.size() == 0);
    }
}

TEST_CASE("Pushing Products onto the stack", "[stack], [push]")
{
    Product first("Best Buy", "Acer Aspire", 150);
    Product second("Goodwill", "Macbook Air", 15000);
    Product third("Fry's", "Sony Vaio", 230);
    Product fourth("Target", "HP notepad", 120);
    Product fifth("Walmart", "Google chromebook", 100);
    Product sixth("Fred Meyers", "lenovo thinkpad", 1000);

    Product_Stack stack;

    SECTION("First push")
    {
        stack.push(first);

        REQUIRE(stack.top() == first);
        CHECK(stack.size() == 1);
    }
    SECTION("Multiple pushes")
    {
        stack.push(first).push(second).push(third);

        REQUIRE(stack.top() == third);
        REQUIRE(stack.bottom() == first);
        CHECK(stack.size() == 3);
    }
    SECTION("Push more elements than the array size")
    {
        stack.push(first).push(second).push(third);
        stack.push(fourth).push(fifth).push(sixth);

        REQUIRE(stack.top() == sixth);
        REQUIRE(stack.bottom() == first);
        CHECK(stack.size() == 6);

    }
}

TEST_CASE("Popping the top of the stack", "[stack], [pop]")
{
    Product first("Best Buy", "Acer Aspire", 150);
    Product second("Goodwill", "Macbook Air", 15000);
    Product third("Fry's", "Sony Vaio", 230);
    Product fourth("Target", "HP notepad", 120);
    Product fifth("Walmart", "Google chromebook", 100);
    Product sixth("Fred Meyers", "lenovo thinkpad", 1000);

    Product_Stack stack;
    Product_Stack empty;

    stack.push(first).push(second).push(third);

    SECTION("Pop a populated stack")
    {
        REQUIRE(stack.pop().size() == 2);
        REQUIRE(stack.pop(sixth) == second);
    }
    SECTION("Pop an empty stack")
    {
        REQUIRE(empty.pop().empty());
    }
    SECTION("A stack with multiple nodes")
    {
        stack.push(fourth).push(fifth).push(sixth);

        REQUIRE(stack.pop().size() == 5);
        REQUIRE(stack.top() == fifth);

        REQUIRE(stack.pop().size() == 4);
        REQUIRE(stack.top() == fourth);
    }

}

TEST_CASE("Clearing a stack", "[stack], [clear]")
{
    Product first("Best Buy", "Acer Aspire", 150);
    Product second("Goodwill", "Macbook Air", 15000);
    Product third("Fry's", "Sony Vaio", 230);
    Product fourth("Target", "HP notepad", 120);
    Product fifth("Walmart", "Google chromebook", 100);
    Product sixth("Fred Meyers", "lenovo thinkpad", 1000);


    Product_Stack stack;
    Product_Stack empty;

    stack.push(first).push(second).push(third);


    SECTION("A populated stack")
    {
        stack.clear_stack();

        REQUIRE(stack.empty());
    }
    SECTION("A stack with multiple nodes")
    {
        stack.push(fourth).push(fifth).push(sixth);

        stack.clear_stack();

        REQUIRE(stack.empty());

    }
    SECTION("An empty stack")
    {
        empty.clear_stack();

        REQUIRE(empty.empty());
    }
}

TEST_CASE("Peek top and bottom of the stack", "[stack], [peek]")
{
    Product_Stack stack;

    SECTION("empty stack returns a default product")
    {
        REQUIRE_THROWS(stack.top());
        REQUIRE_THROWS(stack.bottom());
    }
}
