/*
File: project.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "project.h"

Project::Project() 
    : _attributes(Attributes()) {}

Project::Project(const Attributes& args)
    : _attributes(args) {}

Project::Project(const Project& src)
    : _attributes(src._attributes) {}

Project::~Project() {}

const Project::string& Project::name() const
{
    return _attributes[0];
}

bool Project::operator == (const Project& rhs) const
{
    return _attributes[0] == rhs._attributes[0];
}

bool Project::operator != (const Project& rhs) const
{
    return !(*this == rhs);
}

bool Project::operator < (const Project& rhs) const
{
    return _attributes[0] < rhs._attributes[0];
}

bool Project::operator > (const Project& rhs) const
{
    return !(*this < rhs);
}
