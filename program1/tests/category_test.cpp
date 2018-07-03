/*
File: project_test.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include <catch.hpp>
#include "category.h"

TEST_CASE("Constructing categories", "[category], [constructors]")
{
    SECTION("Default construction")
    {
        SString keys[] = { "Name", "Due", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        bool assert = assignments.size() == 0;
        REQUIRE(assert);
    }
} 

TEST_CASE("Adding projects to the category", "[category], [modifier]")
{
    SECTION("Adding one project")
    {
        SString keys[] = { "Name", "Due", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        Project::Attributes attributes;
        Category::Fields::const_iterator it;

        for(it = assignments.fields().begin(); it != assignments.fields().end(); ++it)
        {
            attributes[*it] =  "Value 1";
        }

        REQUIRE(assignments.add_project(attributes));
 
    }
    /*SECTION("Adding duplicate projects")
    {
        SString keys[] = { "Name", "Due", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        Project::Attributes attributes;
        Category::Fields::const_iterator it;

        for(it = assignments.fields().begin(); it != assignments.fields().end(); ++it)
        {
            attributes[*it] =  "Value 1";
        }

        REQUIRE(assignments.add_project(attributes));

        REQUIRE(!assignments.add_project(attributes));
    }
    SECTION("Adding multiple projects")
    {
        
    }*/
} 