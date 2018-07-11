/*
File: category_test.cpp

Description: Unit tests for the Category ADT

Author: Alexander DuPree

Date: 07/11/2018
*/

#include <iostream>
#include <catch.hpp>
#include "category.h"

TEST_CASE("Constructing categories", "[category], [constructors]")
{
    SECTION("Default construction")
    {
        Category assignments;

        bool assert = assignments.size() == 0;
        REQUIRE(assert);
    }
    SECTION("Value construction")
    {
        Category readings("Readings");

        bool assert = readings.name() == "Readings";
        REQUIRE(assert);
    }
} 

TEST_CASE("Adding projects to the category", "[category], [modifier]")
{
    SECTION("Adding one project")
    {
        SString attributes[] = { "reading 1", "july 4th", "9:00",
                                 "july 5th", "arrays" };

        Project project(attributes);

        Category category("Readings");

        REQUIRE(category.add_project(project));
    }

    SECTION("Adding duplicate projects")
    {
        SString attributes[] = { "reading 1", "july 4th", "9:00",
                                 "july 5th", "arrays" };

        Project project(attributes);

        Category category("Readings");

        REQUIRE(category.add_project(project));

        REQUIRE(!category.add_project(project));
    }
    SECTION("Adding multiple projects")
    {
        SString attributes[5];
        Category category("categories");
        
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 1";
        }

        Project project1(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 2";
        }

        Project project2(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 3";
        }

        Project project3(attributes);

        REQUIRE(category.add_project(project3));
        REQUIRE(category.add_project(project2));
        REQUIRE(category.add_project(project1));

        //category.display_projects();
    }
} 

TEST_CASE("Finding projects", "[category], [find]")
{
    SECTION("A populated category")
    {
        SString attributes[5];
        Category category("categories");
        
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 1";
        }

        Project project1(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 2";
        }

        Project project2(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 3";
        }

        Project project3(attributes);

        REQUIRE(category.add_project(project3));
        REQUIRE(category.add_project(project2));
        REQUIRE(category.add_project(project1));

        bool assert = category.find_project("Value 1")->name() == "Value 1";
        REQUIRE(assert);
    }
    SECTION("An empty category")
    {
        Category category("stuff");
        bool assert = category.find_project("reading 1") == category.end();
        REQUIRE(assert);
    }
}

TEST_CASE("Removing a projct", "[category], [remove]")
{
    SECTION("A populated category")
    {
        SString attributes[5];
        Category category("categories");
        
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 1";
        }

        Project project1(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 2";
        }

        Project project2(attributes);
 
        for (unsigned i = 0; i < 5; ++i)
        {
            attributes[i] = "Value 3";
        }

        Project project3(attributes);

        REQUIRE(category.add_project(project3));
        REQUIRE(category.add_project(project2));
        REQUIRE(category.add_project(project1));

        REQUIRE(category.remove_project("Value 3"));

        //category.display_projects();

    }
    SECTION("An empty category")
    {
        Category category("Stuff");

        REQUIRE(!category.remove_project("Value 1"));
    }
}

