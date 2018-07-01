/*
File: project.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "project.h"

Project::Project() : attributes(Attributes()) {}

Project::Project(Attributes args) : attributes(args) {}

Project::~Project() {}

Project::iterator Project::begin()
{
    return attributes.begin();
}

Project::const_iterator Project::begin() const
{
    return attributes.begin();
}

Project::iterator Project::end()
{
    return attributes.end();
}

Project::const_iterator Project::end() const
{
    return attributes.end();
}

std::ostream& operator << (std::ostream& os, const Project& project)
{
    Project::const_iterator it;
    for (it = project.begin(); it != project.end(); ++it)
    {
        os << it->key << ":\t" << it->value << std::endl;
    }
    return os;
}

bool Project::operator==(const Project& rhs) const
{
    return attributes == rhs.attributes;
}

bool Project::operator != (const Project& rhs) const
{
    return !(*this == rhs);
}

bool Project::operator < (const Project& rhs) const
{
    return attributes < rhs.attributes;
}

bool Project::operator > (const Project& rhs) const
{
    return !(*this < rhs);
}
