/*
File: main.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "database.h"
#include "interface.h"

class database_item : public menu_item
{
  public:
    Database* database;

    database_item(Database* database) : database(database) {}
};

struct display_projects: public database_item
{
    display_projects(Database* database) : database_item(database) {}

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

struct add_project : public database_item
{

    add_project(Database* database) : database_item(database) {}

    static const int FIELDS = 5;

    static const char* FIELD_NAMES[FIELDS];

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
struct remove_category : public database_item
{
    remove_category(Database* database) : database_item(database) {}

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

struct add_category : public database_item
{
    add_category(Database* database) : database_item(database) {}

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

struct display_categories : public database_item
{
    display_categories(Database* database) : database_item(database) {}

    const char* option() const { return "Display Categories"; }

    void action()
    {
        database->display_categories();
    }
};

struct database_model : public menu_model
{

    static const unsigned SIZE = 5;

    Database database;

    unsigned size() const 
    {
        return SIZE;
    }

    void build(menu_item**& menu)
    {
        build_database();

        menu = new menu_item*[SIZE];

        menu[0] = new add_category(&database);
        menu[1] = new display_categories(&database);
        menu[2] = new remove_category(&database);
        menu[3] = new display_projects(&database);
        menu[4] = new add_project(&database);
    }

    void build_database()
    {
        const int SIZE = 3;
        const char* categories[SIZE] = { "assignments",
                                         "readings",
                                         "labs" };

        for(unsigned i = 0; i < SIZE; ++i)
        {
            if(!database.add_category(categories[i]))
            {
                return; // TODO throw exception
            }
        }
        return; // TODO throw exception
    }
};

/* Static variable definitions */
const char* add_project::FIELD_NAMES[FIELDS] = { "Name: ", "Due Date: ",
                                                 "Due Time: ", "Late Date: ",
                                                 "Data Structure: " };


