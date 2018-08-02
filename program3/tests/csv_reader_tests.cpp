/*
File: csv_reader.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/


#include "catch.hpp"
#include "sstring.h"
#include "csv.h"

TEST_CASE("Constructing csv reader objects", "[csv], [constructor]")
{
    SECTION("Default Construction")
    {
        CSV::Reader reader("Shopping.csv");

        REQUIRE(!reader.eof());
    }
    SECTION("Construction with an invalid filename")
    {
        REQUIRE_THROWS(CSV::Reader("invalid file"));
    }
}

TEST_CASE("Determining columns and rows", "[csv], [columns], [rows]")
{
    CSV::Reader reader("Shopping.csv", '|');

    SECTION("Determine columns")
    {
        REQUIRE(reader.columns() == 4);
    }
    SECTION("Determine rows")
    {
        REQUIRE(reader.rows() == 959);
    }
}

TEST_CASE("Reading file lines", "[csv], [readline]")
{
    CSV::Reader reader("Shopping.csv", '|');

    SECTION("Storing each attribute into an array")
    {
        SString fields[] = { "name", "description", "color", "website" };

        SString attributes[reader.columns()];

        reader.readline(attributes);

        for(unsigned i = 0; i < reader.columns(); ++i)
        {
            REQUIRE(attributes[i] == fields[i]);
        }
    }
    SECTION("Reading from eof fails")
    {
        reader.seek(reader.rows());

        SString attributes[reader.columns()];

        REQUIRE_FALSE(reader.readline(attributes));
    }
}
