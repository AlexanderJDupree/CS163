/*
File: main.cpp

Brief: main is the entry point for the program 3 application.

Author: Alexander DuPree

Class: CS163

Assignment: program 3

Date: 08/03/2018
*/

#include "program_menu.h"

void intro();

int main()
{
    intro();

    int table_size = Interface::get_input<int>();

    if(table_size <= 0)
    {
        table_size = 1223;
    }

    program_menu_model model(table_size);

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
        "\n                         Program 3"
        "\n"
        "\n"
        "\n                 Author: Alexander DuPree"
        "\n"
        "\n"
        "\n"
        "=============================================================\n";

    Interface::pause_console();
    Interface::clear_screen();

    std::cout << 
        "Enter the table size, (Note that a large prime number like"
        " 1223 or 1811 will yield the best storage results):";
    return;
}

