/*
File: category.cpp

Description: Definition for Category ADT's methods. Because Category is a 
             wrapper class, most functions are dependent on the Projects 
             containers implementation.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#include "category.h"

// Default constructor
Category::Category()
    : _name(""), _projects(Projects()) {}

// Value constructor
Category::Category(const string& name) 
    : _name(name), _projects(Projects()) {}

// Copy constructor
Category::Category(const Category& origin)
    : _name(origin._name), _projects(origin._projects) {}

const Category::string& Category::name() const
{
    return _name;
}

bool Category::add_project(const Project& project)
{
    return _projects.add_unique(project);
}

bool Category::remove_project(const string& name)
{
    // Instantiate a functor with a named state
    remove_functor functor = { name };

    return _projects.remove_if(functor);
}

void Category::display_projects()
{
    for (const_iterator it = _projects.begin(); it != _projects.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return;
}

Category::const_iterator Category::find_project(const string& name)
{
    const_iterator it;
    for (it = _projects.begin(); it != _projects.end(); ++it)
    {
        if (it->name() == name)
        {
            return it;
        }
    }
    return it;
}

Category::const_iterator Category::begin() const
{
    return _projects.begin();
}

Category::const_iterator Category::end() const
{
    return _projects.end();
}

Category::size_type Category::size() const
{
    return _projects.size();
}

bool Category::operator == (const self_type& rhs) const
{
    return _name == rhs._name;
}

bool Category::operator != (const self_type& rhs) const
{
    return !(*this == rhs);
}

bool Category::operator < (const self_type& rhs) const
{
    return _name < rhs._name;
}

bool Category::operator > (const self_type& rhs) const
{
    return !(*this < rhs);
}

std::ostream& operator << (std::ostream& os, const Category& category)
{
    os << "Category: " << category.name() << '\n'
       << "No. of Projects: " << category.size() << '\n';
    return os;
}
