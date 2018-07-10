/*
File: main.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include "interface.h"
#include "database.h"

// Builds database with predefined categories on application star
bool build_database(Database& database);

struct exit_application : public menu_item
{
    bool exit;

    exit_application() : exit(false) {}

    bool operator()() { return exit; }

    const char* option() const { return "Exit Application"; }

    void action() 
    { 
        std::cout << "Have a nice day!" << std::endl;
        exit = true; 
    }
};

int main()
{
    // Instantiate database
    Database database;

    // Add predefined categories to the database
    build_database(database);

    exit_application exit;

    menu_item* menu[] = { &exit };

    Interface UI(menu, 1);

    while (!exit())
    {
        UI.display_menu();

        UI.run_action(Interface::get_input("\n> ") -1);
    }

    return 0;
}

bool build_database(Database& database)
{
    const int SIZE = 3;
    const char* categories[SIZE] = { "Assignments",
                                     "Readings",
                                     "Labs" };
    for(unsigned i = 0; i < SIZE; ++i)
    {
        if(!database.add_category(categories[i]))
        {
            return false;
        }
    }
    return true;
}
