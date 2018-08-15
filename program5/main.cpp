/*
File: main.cpp

Brief: main is the entry point for the program 4 application.

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/03/2018
*/

#include "interface.h"
#include "city_graph.h"

void intro();

int main()
{
    intro();

    City_Graph graph;

    graph.add_city("Portland").add_city("Gresham").add_city("Hillsboro")
         .add_city("Troutdale").add_city("Vancouver");

    graph.add_road("Portland", "Gresham", Road("I84", 20));
    graph.add_road("Portland", "Vancouver", Road("I205", 15));
    graph.add_road("Gresham", "Troutdale", Road("Halsey", 5));

    graph.display_cities();

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

