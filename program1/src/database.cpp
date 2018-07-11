/*
File: database.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
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

bool Database::add_project(const string& name, const Project& project)
{

    Categories::iterator it = find_category(name);
    if(it == _categories.end())
    {
        // Category doesn't exist
        return false;
    }

    return it->add_project(project);
}

bool Database::remove_project(const string& category, const string& project)
{
    Categories::iterator it = find_category(category);
    if(it == _categories.end())
    {
        // Category doesn't exist
        return false;
    }

    return it->remove_project(project);
}

bool Database::display_projects(const string& category)
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


