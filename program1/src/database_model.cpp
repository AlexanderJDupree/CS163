/*
File: database_model.cpp

Description: Implementation file for the database_model class. Because the menu
             options are known before application start the menu array containing
             the options is hard coded.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#include "database_model.h"

void database_model::build(menu_item**& menu)
{
    build_database();

    menu = new menu_item*[SIZE];

    // This is the menu to be used in the application, if new menu_items are 
    // created then it must be added to this table.
    menu[0] = new add_category(&database);
    menu[1] = new display_categories(&database);
    menu[2] = new remove_category(&database);
    menu[3] = new display_projects(&database);
    menu[4] = new add_project(&database);
    menu[5] = new remove_project(&database);
}

void database_model::build_database()
{
    const int SIZE = 3;
    const char* categories[SIZE] = { "assignments",
                                     "readings",
                                     "labs" };

    for(unsigned i = 0; i < SIZE; ++i)
    {
        if(!database.add_category(categories[i]))
        {
            throw database_error("Database failed to build");
        }
    }
    return;
}

unsigned database_model::size() const
{
    return SIZE;
}

/* Static variable definitions */
const char* add_project::FIELD_NAMES[FIELDS] = { "Name: ", "Due Date: ",
                                                 "Due Time: ", "Late Date: ",
                                                 "Data Structure: " };

