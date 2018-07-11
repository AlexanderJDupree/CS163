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

struct display_projects: public menu_item
{
    Database* database;

    display_projects(Database* database) : database(database) {}

    const char* option() const { return "Display All Projects In a Category"; }

    void action()
    {
        SString category;
        Interface::get_input("\nEnter the name of the category: ", category);

        if(!database->display_projects(category))
        {
            std::cout << "\n\t'" << category << "' does not exist.\n";
        }
    }
};

struct add_project : public menu_item
{

    Database* database;

    static const int FIELDS = 5;
    static const char* FIELD_NAMES[FIELDS];

    add_project(Database* database) : database(database) {}

    const char* option() const { return "Add a Project"; }

    void action()
    {
        SString category;
        SString attributes[FIELDS];

        Interface::get_input("\nEnter the name of the category: ", category);

        for (unsigned i = 0; i < FIELDS; ++i)
        {
            std::cout << "\nEnter the Project ";
            Interface::get_input(FIELD_NAMES[i], attributes[i]);
        }

        if(database->add_project(category, Project(attributes)))
        {
            std::cout << "\n\t'" << attributes[0] << "' was added to the '"
                      << category << "' category.\n";
        }
        else
        {
            std::cout << "\n\tFailed to add '" << attributes[0] << "' to the '"
                      << category << "' category.\n";
        }
    }

};

const char* add_project::FIELD_NAMES[FIELDS] = { "Name: ", "Due Date: ",
                                                 "Due Time: ", "Late Date: ",
                                                 "Data Structure: " };

struct remove_category : public menu_item
{
    Database* database;

    remove_category(Database* database) : database(database) {}

    const char* option() const { return "Remove a Category"; }

    void action()
    {
        SString input;
        Interface::get_input("\nEnter the name of the category: ", input);

        if (database->remove_category(input))
        {
            std::cout << "\n\t" << input << " was removed!\n";
        }
        else
        {
            std::cout << "\n\tCategory '" << input << "' does not exist\n";
        }
    }

};

struct add_category : public menu_item
{
    Database* database;

    add_category(Database* database) : database(database) {}

    const char* option() const { return "Add a Category"; }

    void action()
    {
        SString input;
        Interface::get_input("\nEnter the name of the category: ", input);

		if (database->add_category(input))
        {
            std::cout << "\n\t'" << input <<"' category was added!\n";
        }
        else
        {
            std::cout << "\n\t" << input << " was not added: duplicate entry\n";
        }
    }
};

struct display_categories : public menu_item
{
    const Database* database;

    display_categories(const Database* database) : database(database) {}

    const char* option() const { return "Display Categories"; }

    void action()
    {
        database->display_categories();
    }
};

struct exit_application : public menu_item
{
    bool exit;

    exit_application() : exit(false) {}

    bool operator()() { return exit; }

    const char* option() const { return "Exit Application"; }

    void action() 
    { 
        std::cout << "Have a nice day!\n";
        exit = true; 
    }
};

int main()
{
    // Instantiate database
    Database database;

    // Add predefined categories to the database
    build_database(database);

	// Instantiate menu options - connect them to the database 
    exit_application   exit;
    add_category       add_cat(&database);
    display_categories display_cat(&database);
    remove_category    remove_cat(&database);
    add_project        add_proj(&database);
    display_projects   display_projs(&database);

    // Stores the addresses of the menu objects into an array so the interface
    // can interact with them
    menu_item* menu[] = { &display_cat, &add_cat, &remove_cat, 
                          &add_proj, &display_projs, &exit };

    // Instantiates UI with the location of the menu objects
    Interface UI(menu, 6);

    // input container
    unsigned input = 0;
    while (!exit())
    {
        UI.display_menu();

        UI.run_action(--Interface::get_input("\n> ", input));
    }

    return 0;
}

// TODO build database from an input file
bool build_database(Database& database)
{
    const int SIZE = 3;
    const char* categories[SIZE] = { "assignments",
                                     "readings",
                                     "labs" };
    for(unsigned i = 0; i < SIZE; ++i)
    {
        if(!database.add_category(categories[i]))
        {
            return false;
        }
    }
    return true;
}

