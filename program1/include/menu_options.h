/*
File: menu_options.h

Description: menu_options contains the concrete definition of the menu_item
             abstract base class. each database_item holds a pointer to a 
             database object but does not manage the objects resources. 

             The database_item primary responsibility is to execute a specific
             action with the database and report on the fail/success of that 
             action

             The database_item does uses the default destructor as it does not
             manage any resources, the Database pointer is deleted when it goes
             out of scope. The Database itself is handled by the database_model 
             object.

Author: Alexander DuPree

Date: 07/11/2018

*/

#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include "database.h"
#include "interface.h"

struct database_item : public menu_item
{
  public:

    // Each database_item requires a database to be linked with and cannot be
    // instantiated without a pointer to a valid database
    database_item(Database* database) : database(database) {}

  protected:

    Database* database;
};

struct remove_project : public database_item
{
    remove_project(Database* database) : database_item(database) {}

    const char* option() const { return "Remove a Project in a Category"; }

    void action()
    {
        SString category;
        Interface::get_input("\nEnter the name of the category: ", category);

        SString project;
        Interface::get_input("\nEnter the name of the project: ", project);

        try
        {

            database->remove_project(category, project);
            std::cout << "\n\t'" << project << "' was removed from '" 
                      << category << "' category.\n";
        }
        catch(const database_error& err)
        {
            std::cout << "\n\tFailed to remove '" << project << "': " 
                      << err.what() << '\n';
        }
    }
};

struct display_projects : public database_item
{
    display_projects(Database* database) : database_item(database) {}

    const char* option() const { return "Display All Projects In a Category"; }

    void action()
    {
        SString category;
        Interface::get_input("\nEnter the name of the category: ", category);

        try
        {
            database->display_projects(category);
        }
        catch(const database_error& err)
        {
            std::cout << "\n\t'" << category << "': " << err.what() << '\n';
        }
    }
};

struct add_project : public database_item
{

    add_project(Database* database) : database_item(database) {}

    /*
    The Project data type is a static class that holds 5 attributes.
    Becuase these attribtues are known, the name of the fields and the number of
    fields is hard coded. In the future if the Project ADT is changed, this 
    menu_item must change as well. 
    */
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

        try
        {
            database->add_project(category, Project(attributes));

            std::cout << "\n\t'" << attributes[0] << "' was added to the '"
                      << category << "' category.\n";
        }
        catch(const database_error& err)
        {
            std::cout << "\n\tFailed to add '" << attributes[0] << "': "
                      << err.what() << '\n';
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

#endif // MENU_OPTIONS_H
