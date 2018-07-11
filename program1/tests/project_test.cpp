/*
File: project_test.cpp

Description: Unit tests for the Project ADT

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 06/27/2018
*/

#include <iostream>
#include <catch.hpp>
#include "project.h"

TEST_CASE("Constructing project object", "[project], [constructors]")
{
    SECTION("Default construction")
    {
        Project project;

        bool assert = project.name() == "";
        REQUIRE(assert);
    }
    SECTION("Value construction with an array")
    {
        SString attributes[] = { "assignment 1", 
                                 "due date", 
                                 "late date",
                                 "due time", 
                                 "data structure" };
        
        Project project(attributes);

        bool assert = project.name() == "assignment 1";
        REQUIRE(assert);
    }
}

