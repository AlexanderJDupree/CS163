/*
File: project.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "category.h"

Category::Category(const string& name, const Fields& fields) 
    : _name(name), _fields(fields), _projects(Projects()) {}

const Category::string& Category::name()
{
    return _name;
}

const Category::Fields& Category::fields()
{
    return _fields;
}

bool Category::add_project(Project::Attributes attributes)
{
    return _projects.add(Project(attributes));
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
