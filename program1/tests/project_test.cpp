/*
File: project_test.cpp

Description:

Author: Alexander DuPree

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
        

    }
    SECTION("Value construction with an array")
    {
        SString attributes[] = { "assignment 1", 
                                 "due date", 
                                 "late date",
                                 "due time", 
                                  "data structure" };
        
        Project project(*attributes, attributes + 1, attributes + 5);
    }
}