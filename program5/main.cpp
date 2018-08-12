/*
File: main.cpp

Brief: main is the entry point for the program 4 application.

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/03/2018
*/

#include "interface.h"

void intro();

int main()
{
    intro();

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
        "\n                         Program 4"
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

