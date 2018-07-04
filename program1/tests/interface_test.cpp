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

       // UI.display_menu();
    }
    SECTION("Building and displaying a menu")
    {
        menu_item* menus[] = {new option_1(), new option_2(), new option_3()};
        Interface::Menu menu(menus, menus + 3);

        Interface UI(menu);

        //UI.display_menu();

    }
}
