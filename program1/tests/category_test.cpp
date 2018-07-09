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
/*
TEST_CASE("Adding projects to the category", "[category], [modifier]")
{
    SECTION("Adding one project")
    {
        SString keys[] = { "Name", "Due", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        Category::Fields attributes(3, "Value 1");

        REQUIRE(assignments.add_project(attributes));
 
    }
    SECTION("Adding duplicate projects")
    {
        SString keys[] = { "Name", "Due", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        Category::Fields attributes(3, "Value 1");

        REQUIRE(assignments.add_project(attributes));

        REQUIRE(!assignments.add_project(attributes));
    }
    SECTION("Adding multiple projects")
    {
        SString keys[] = { "Name", "Due Date", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);


        Category::Fields attributes(3, "Value 1");

        REQUIRE(assignments.add_project(attributes));


        attributes = Category::Fields(3, "Value 2");

        REQUIRE(assignments.add_project(attributes));
 

        attributes = Category::Fields(3, "Value 3");

        REQUIRE(assignments.add_project(attributes));


        attributes = Category::Fields(3, "Value 4");

        REQUIRE(assignments.add_project(attributes));
    }
    SECTION("Adding invalid project attributes")
    {
        SString keys[] = { "Name", "Due Date", "Data Structure" };
        Category::Fields fields(keys, keys + 3);

        Category assignments("assignments", fields);

        Category::Fields attributes;

        REQUIRE(!assignments.add_project(attributes));
    }
} 

TEST_CASE("Finding projects", "[category], [find]")
{
    SECTION("A populated category")
    {
        SString fields[] = { "Name", "Due Date", "Data Structure" };
        Category labs("labs", fields, fields + 3);

    }
}
*/