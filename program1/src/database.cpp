/*
File: database.cpp

Description: Implementation file for the Database ADT.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#include "database.h"

Database::Database()
    : _categories(Categories()) {}

bool Database::add_category(const string& name)
{
    return _categories.add_unique(Category(name));
}

bool Database::remove_category(const string& name)
{
    // Create a functor object that compares to the name target
    remove_functor functor = { name };

    return _categories.remove_if(functor);
}

void Database::display_categories() const
{
    Categories::const_iterator it;

    std::cout << std::endl;
    for(it = _categories.begin(); it != _categories.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return;
}

void Database::add_project(const string& name, const Project& project)
{

    Categories::iterator it = find_category(name);

    if(!it->add_project(project))
    {
        throw database_error("duplicate entry");
    }

    return;
}

void Database::remove_project(const string& category, const string& project)
{
    Categories::iterator it = find_category(category);

    if (!it->remove_project(project))
    {
        throw database_error("project does not exist");
    }

    return;
}

void Database::display_projects(const string& category)
{
    Categories::iterator it = find_category(category);

    std::cout << '\n' <<  *it << std::endl;
    it->display_projects();
    return;
}

Database::Categories::iterator Database::find_category(const string& name)
{
    Categories::iterator it;
    for(it = _categories.begin(); it != _categories.end(); ++it)
    {
        if(it->name() == name)
        {
            return it;
        }
    }

    // Category was not found if the loop completes
    throw database_error("category not found");
}

Database::size_type Database::size() const
{
    return _categories.size();
}

bool Database::empty()
{
    return _categories.empty();
}

