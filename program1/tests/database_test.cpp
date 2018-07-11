/*
File: database_test.cpp

Description: Unit tests for the database ADT

Author: Alexander DuPree

Date: 07/11/2018
*/

#include <iostream>
#include <catch.hpp>
#include "database.h"

TEST_CASE("Constructing Databse objects", "[database], [constructors]")
{
    SECTION("Default construction")
    {
        Database database;

        REQUIRE(database.empty());
    }
}

TEST_CASE("Adding categories", "[database], [modifiers], [add_category]")
{
    SECTION("Adding unique categories")
    {
        Database database;

        REQUIRE(database.add_category("cat 1"));
        REQUIRE(database.add_category("cat 2"));
        REQUIRE(database.add_category("cat 3"));

        //database.display_categories();
    }
    SECTION("Adding duplicate categories")
    {
        Database database;

        REQUIRE(database.add_category("cat 1"));
        REQUIRE(!database.add_category("cat 1"));
    }
}

TEST_CASE("Removing categories", "[database], [modifiers], [remove_category]")
{
    SECTION("Removing from a populated database")
    {
        Database database;

        database.add_category("cat 1");
        database.add_category("cat 2");

        REQUIRE(database.remove_category("cat 2"));

        bool assert = database.size() == 1;
        REQUIRE(assert);
    }
}

TEST_CASE("Adding/Removing projects to categories", "[database], [modifiers], [add_project]")
{
    SECTION("Adding projects")
    {
        Database database;
        SString attributes[] = { "assignment 1", 
                                 "due date", 
                                 "late date",
                                 "due time", 
                                 "data structure" };
            
        Project project(attributes);


        database.add_category("cat 1");
        database.add_category("cat 2");

        database.add_project("cat 2", project);
        database.add_project("cat 2", Project());

        bool assert = database.size() == 2;
        REQUIRE(assert);

        //database.display_projects("cat 2");

    }
    SECTION("Adding duplicate projects")
    {
        Database database;
        SString attributes[] = { "assignment 1", 
                                 "due date", 
                                 "late date",
                                 "due time", 
                                 "data structure" };
            
        Project project(attributes);


        database.add_category("cat 1");
        database.add_category("cat 2");

        database.add_project("cat 2", project);
        REQUIRE_THROWS(database.add_project("cat 2", project));

        //database.display_categories();
    }
    SECTION("Adding projects to an empty database")
    {
        Database database;

        Project project;

        REQUIRE_THROWS(database.add_project("hey", project));
    }
}

