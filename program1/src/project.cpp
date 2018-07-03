/*
File: project.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "project.h"

Project::Project() 
    : _attributes(Attributes()), _name("") {}

Project::Project(const Attributes& args)
    : _attributes(args) 
{
    Attributes::const_iterator it;
    if((it = args.find("Name")) == args.end())
    {
        throw std::invalid_argument("Name identifier not found");
    }

    _name = it->second;
}

Project::Project(const Project& project)
    : _attributes(project._attributes) {}

Project::~Project() {}

const Project::string& Project::name() const
{
    return _name;
}

std::ostream& operator << (std::ostream& os, const Project& project)
{
    Project::Attributes::const_iterator it;
    for(it = project._attributes.begin(); it != project._attributes.end(); ++it)
    {
        os << it->first << ":\t" << it->second << std::endl;
    }
    return os;
}

bool Project::operator == (const Project& rhs) const
{
    return _name == rhs._name;
}

bool Project::operator != (const Project& rhs) const
{
    return !(*this == rhs);
}

bool Project::operator < (const Project& rhs) const
{
    return _name < rhs._name;
}

bool Project::operator > (const Project& rhs) const
{
    return !(*this < rhs);
}
