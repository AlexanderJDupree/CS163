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
}