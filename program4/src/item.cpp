/*
File: item.h

Brief: Implementation file for the Item class, defines basic methods for 
       inspection, mutation, and construction of the Item object.

Author: Alexander DuPree

Class: CS163

Assignment: program 3

Date: 08/03/2018
*/

#include "item.h"

Item::Item(string name, string description, string color, string website)
    : _name(name), _description(description), _color(color), _website(website) {}

const Item::string& Item::name() const
{
    return _name;
}

const Item::string& Item::description() const
{
    return _description;
}

const Item::string& Item::color() const
{
    return _color;
}

const Item::string& Item::website() const
{
    return _website;
}

Item& Item::name(const string& name)
{
    _name = name;
    return *this;
}

Item& Item::description(const string& description)
{
    _description = description;
    return *this;
}

Item& Item::color(const string& color)
{
    _color = color;
    return *this;
}

Item& Item::website(const string& website)
{
    _website = website;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "NAME\t\tCOLOR\t\tWEBSITE\n" << SString(50, '-') << '\n'
       << item._name.truncate(16) << item._color.truncate(16) << item._website
       << '\n' << SString(50, '=') << "\nDESCRIPTION: \n'" << item._description 
       << "'\n";

    return os;
}

bool Item::operator < (const self_type& rhs) const
{
    return _name < rhs._name;
}
bool Item::operator > (const self_type& rhs) const
{
    return !(*this < rhs);
}
bool Item::operator == (const self_type& rhs) const
{
    return _name == rhs.name();
}
bool Item::operator != (const self_type& rhs) const
{
    return !(*this == rhs);
}
bool Item::operator <= (const self_type& rhs) const
{
    return *this < rhs || *this == rhs;
}
bool Item::operator >= (const self_type& rhs) const
{
    return !(*this <= rhs);
}

