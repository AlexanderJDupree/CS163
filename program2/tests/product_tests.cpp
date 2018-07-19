/*
File: product_tests.cpp

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "catch.hpp"
#include "product.h"

TEST_CASE("Constructing Product objectes", "[product], [constructors]")
{
    SECTION("Default Construction")
    {
        Product product;

        REQUIRE(product.store() == "");
        REQUIRE(product.model() == "");
        REQUIRE(product.price() == 0);
    }
    SECTION("Value construction")
    {
        Product product("Best Buy", "Acer Aspire", 150);

        REQUIRE(product.store() == "Best Buy");
        REQUIRE(product.model() == "Acer Aspire");
        REQUIRE(product.price() == 150);
    }
}

TEST_CASE("Add matched features to the product", "[product], [matches]")
{
    SString features[] = { "16GB RAM", "1TB SSD", "GTX1080TI" };
    SECTION("Standard Features")
    {
        Product product("Best Buy", "Acer Aspire", 150);

        for (unsigned i = 0; i < 3; ++i)
        {
            product.add_match(features[i]);
        }

        REQUIRE(product.matches() == 3);
    }
}

TEST_CASE("Displaying products", "[product], [display]")
{
    Product product("Best Buy", "Acer Aspire", 150);

    SECTION("With matching features")
    {

        SString features[] = { "16GB RAM", "1TB SSD", "GTX1080TI" };
        for (unsigned i = 0; i < 3; ++i)
        {
            product.add_match(features[i]);
        }

        std::ostringstream oss;

        oss << product;

        REQUIRE(oss.str() ==
                "\nSTORE:\tBest Buy\nMODEL:\tAcer Aspire\nPRICE:\t150\n"
                "\nMatched Features: 3\n============================\n"
                "16GB RAM\n1TB SSD\nGTX1080TI\n============================\n");
    }
    SECTION("With no matching features")
    {
        std::ostringstream oss;

        oss << product;
        REQUIRE(oss.str() ==
                "\nSTORE:\tBest Buy\nMODEL:\tAcer Aspire\nPRICE:\t150\n"
                "\nMatched Features: 0\n============================\n"
                "============================\n");
    }

}

TEST_CASE("Comparing for equality", "[product], [equality]")
{
    Product aspire("Best Buy", "Acer Aspire", 150);
    Product aspire2("Fry's", "Acer Aspire", 100);
    Product macbook("Goodwill", "Macbook Air", 150000);

    SECTION("The same models are equal despite different stores and prices")
    {
        REQUIRE(aspire == aspire2);
    }
    SECTION("Different models do not compare equal")
    {
        REQUIRE(aspire != macbook);
    }
}
