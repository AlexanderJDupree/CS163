/*
File: item.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
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

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "NAME\t\tCOLOR\t\tWEBSITE\n" << SString(40, '-') << '\n'
       << item._name.truncate(16) << item._color.truncate(16) << item._website
       << '\n' << SString(40, '=') << "\nDESCRIPTION: \n'" << item._description 
       << '\n';

    return os;
}

