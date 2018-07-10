/*
File: database.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "database.h"

Database::Database()
    : _categories(Categories()) {}

bool Database::add_category(const char* name)
{
    return _categories.add_unique(Category(name));
}

bool Database::remove_category(const char* name)
{
    // Create a functor object that compares to the name target
    remove_functor functor = { name };

    return _categories.remove_if(functor);
}

void Database::display_categories()
{
    Categories::const_iterator it;

    for(it = _categories.begin(); it != _categories.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return;
}

bool Database::add_project(const char* name, const Project& project)
{

    Categories::iterator it = find_category(name);
    if(it == _categories.end())
    {
        // Category doesn't exist
        return false;
    }

    return it->add_project(project);
}

bool Database::remove_project(const char* category, const char* project)
{
    Categories::iterator it = find_category(category);
    if(it == _categories.end())
    {
        // Category doesn't exist
        return false;
    }

    return it->remove_project(project);
}

bool Database::display_projects(const char* category)
{
    Categories::iterator it = find_category(category);
    if(it == _categories.end())
    {
        // Category doesn't exist
        return false;
    }

    std::cout << *it << std::endl;
    it->display_projects();
    return true;
}

Database::Categories::iterator Database::find_category(const char* name)
{
    Categories::iterator it;
    for(it = _categories.begin(); it != _categories.end(); ++it)
    {
        if(it->name() == name)
        {
            return it;
        }
    }
    return it;
}

Database::size_type Database::size() const
{
    return _categories.size();
}

bool Database::empty()
{
    return _categories.empty();
}


