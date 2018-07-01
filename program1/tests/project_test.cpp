/*
File: project_test.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include <catch.hpp>
#include "project.h"

TEST_CASE("Constructing Project objects", "[project], [constructos]")
{
    SECTION("Default construction")
    {
        Project project;

        bool assert = project.begin() == project.end();
        REQUIRE(assert);
    }

    SECTION("Value construction")
    {
        Project::Attributes attributes;

        attributes.push_back(Project::field("Name", "Program #1"));
        attributes.push_back(Project::field("Date", "06/28/2019"));
        attributes.push_back(Project::field("Time", "11:59"));

        Project project(attributes);

        //std::cout << project << std::endl;
    }
}

TEST_CASE("Comparison operators for Proejcts", "[project], [constructors]")
{
    SECTION("Two equal projects")
    {
        Project::Attributes attributes;

        attributes.push_back(Project::field("Name", "Program #1"));
        attributes.push_back(Project::field("Date", "06/28/2019"));
        attributes.push_back(Project::field("Time", "11:59"));

        Project project1(attributes);

        Project project2(attributes);

        bool assert = project1 == project2;

        REQUIRE(assert);

    }
    SECTION("two different projects")
    {
        Project::Attributes attributes;

        attributes.push_back(Project::field("Name", "Program #1"));
        attributes.push_back(Project::field("Date", "06/28/2019"));
        attributes.push_back(Project::field("Time", "11:59"));

        Project project1(attributes);

        attributes.push_back(Project::field("late time", "11:59"));

        Project project2(attributes);

        bool assert = project1 != project2;

        REQUIRE(assert);
    }
    SECTION("ordering of projects")
    {
        Project::Attributes attributes;

        attributes.push_back(Project::field("Name", "assignment"));
        attributes.push_back(Project::field("Date", "06/28/2019"));
        attributes.push_back(Project::field("Time", "11:59"));

        Project project1(attributes);

        attributes[0].value = "book reading";

        Project project2(attributes);

        bool assert = project1 < project2;

        REQUIRE(assert);

    }
    SECTION("ordering of projects with different keys")
    {
        Project::Attributes attributes;

        attributes.push_back(Project::field("Name", "assignment"));
        attributes.push_back(Project::field("Date", "06/28/2019"));
        attributes.push_back(Project::field("Time", "11:59"));

        Project project1(attributes);

        attributes[0].key = "book reading";
        attributes[1].key = "book reading";
        attributes[2].key = "book reading";

        Project project2(attributes);

        bool assert = project1 > project2;

        REQUIRE(assert);


    }
    
}