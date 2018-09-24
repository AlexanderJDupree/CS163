/*
File: item_table.cpp

Brief: Implementation file for teh Item_Table ADT defines methods for adding, 
       removal, and retrieval of Item objects.

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/03/2018
*/

#include <iomanip>
#include "item_table.h"

Item_Table::Item_Table()
    : _table() {}

// Item_Table ADT does not manage any resouces, the default destructor is used
Item_Table::~Item_Table() {}

void Item_Table::add(const Item& item)
{
    _table.insert(item.name(), item);
}

bool Item_Table::remove(const string& item_name)
{
    return _table.erase(item_name);
}

const Item& Item_Table::retrieve(const string& item_name) const
{
    return _table.find(item_name);
}

void Item_Table::clear()
{
    _table.clear();
    return;
}

unsigned Item_Table::size() const
{
    return _table.size();
}

Item_Table::const_iterator Item_Table::begin() const
{
    return _table.begin();
}

Item_Table::const_iterator Item_Table::end() const
{
    return _table.end();
}

void Item_Table::display_diagnostics()
{
    std::cout << "\t\tBINARY TREE DIAGNOSTICS\n" << SString(57, '=')
              << "\nITEMS:\t" << _table.size() << "\nHEIGHT:\t" 
              << _table.height() << "\nLEAVES:\t" << _table.leaves() 
              << '\n' << SString(57, '=');
    return;
}

