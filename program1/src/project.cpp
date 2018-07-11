/*
File: project.cpp

Description: Implementation file for the Project class.

Author: Alexander DuPree

Date: 07/11/2018
*/

#include "project.h"

Project::Project() 
    : _name(""), _due_date(""), _due_time(""), 
      _late_date(""), _data_structure("") {}

Project::Project(const string attributes[])
    : _name(attributes[0]), _due_date(attributes[1]), _due_time(attributes[2]),
      _late_date(attributes[3]), _data_structure(attributes[4]) {}
    
Project::Project(const Project& src)
    : _name(src._name), _due_date(src._due_date), _due_time(src._due_time),
      _late_date(src._late_date), _data_structure(src._data_structure) {}

Project::~Project() {}

const Project::string& Project::name() const
{
    return _name;
}

bool Project::operator == (const self_type& rhs) const
{
    return _name == rhs._name;
}

bool Project::operator != (const self_type& rhs) const
{
    return !(*this == rhs);
}

bool Project::operator < (const self_type& rhs) const
{
    return _name < rhs._name;
}

bool Project::operator > (const self_type& rhs) const
{
    return !(*this < rhs);
}

std::ostream& operator << (std::ostream& os, const Project& project)
{
    os << "Name:\t" << project._name << '\n'
       << "Due Date:\t" << project._due_date << '\n'
       << "Due Time:\t" << project._due_time << '\n'
       << "Late Date:\t" << project._late_date << '\n'
       << "Data Structure:\t" << project._data_structure << '\n';
    return os;
}
