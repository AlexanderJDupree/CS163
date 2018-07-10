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
    const char* option() const { return "option 1"; }

    void action() { return require_true(); }
};

struct option_2 : public menu_item
{
    const char* option() const { return "option 2"; }

    void action() { return require_true(); }
};

struct option_3 : public menu_item
{
    const char* option() const { return "option 3"; }

    void action() { return require_true(); }
};

TEST_CASE("Building a menu", "[interface], [menu]")
{
    SECTION("Building and displaying a menu")
    {
        option_1 opt1;
        option_2 opt2;
        option_3 opt3;

        menu_item* menu[] = { &opt1, &opt2, &opt3 };

        Interface UI(menu, 3);

        UI.display_menu();
    }
}

TEST_CASE("evaluating actions", "[interface], [run_action]")
{
        option_1 opt1;
        option_2 opt2;
        option_3 opt3;

        menu_item* menu[] = { &opt1, &opt2, &opt3 };

        Interface UI(menu, 3);

        UI.display_menu();

        UI.run_action(Interface::get_input("\n> ") - 1);
}
