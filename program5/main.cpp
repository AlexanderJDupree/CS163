/*
File: main.cpp

Brief: main is the entry point for the program 5 application.

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/15/2018
*/

#include "program5_menu.h"

void intro();

int main()
{
    intro();

    roadtrip_menu_model model;

    Interface UI(&model);

    UI.run();

    return 0;
}

void intro()
{
    std::cout <<
        "============================================================="
        "\n"
        "\n"
        "\n"
        "\n"
        "\n                         Program 5"
        "\n"
        "\n"
        "\n                 Author: Alexander DuPree"
        "\n"
        "\n"
        "\n"
        "=============================================================\n";

    Interface::pause_console();
    Interface::clear_screen();

    return;
}

