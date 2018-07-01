/*
File: project_test.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <catch.hpp>
#include "sstring.h"
#include "interface.h"

void require_true()
{
    REQUIRE(true);
    return;
}

struct option_1 : public menu_item
{
    const SString option() const { return "option 1"; }

    void action() { return require_true(); }
};

struct option_2 : public menu_item
{
    const SString option() const { return "option 2"; }

    void action() { return require_true(); }
};

struct option_3 : public menu_item
{
    const SString option() const { return "option 3"; }

    void action() { return require_true(); }
};

TEST_CASE("Building a menu", "[interface], [menu]")
{
    SECTION("Displaying an empty menu")
    {
        Interface UI;

        UI.display_menu();
    }
    SECTION("Building and displaying a menu")
    {
        option_1 opt;
        option_2 opt2;
        option_3 opt3;
        Interface::Menu menu;

        menu.push_back(&opt);
        menu.push_back(&opt2);
        menu.push_back(&opt3);

        Interface UI(menu);

        UI.display_menu();
    }
}