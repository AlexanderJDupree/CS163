/*
File: project.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "project.h"

Project::Project() 
    : _attributes(Attributes()), _identifier("") {}

Project::Project(const Project& src)
    : _attributes(src._attributes), _identifier(src._identifier) {}

Project::~Project() {}

const Project::string& Project::identifier() const
{
    return _identifier;
}

bool Project::operator == (const Project& rhs) const
{
    return _identifier == rhs._identifier;
}

bool Project::operator != (const Project& rhs) const
{
    return !(*this == rhs);
}

bool Project::operator < (const Project& rhs) const
{
    return _identifier < rhs._identifier;
}

bool Project::operator > (const Project& rhs) const
{
    return !(*this < rhs);
}
