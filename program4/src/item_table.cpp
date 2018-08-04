/*
File: item_table.cpp

Brief: Implementation file for teh Item_Table ADT defines methods for adding, 
       removal, and retrieval of Item objects.

Author: Alexander DuPree

Class: CS163

Assignment: program 3

Date: 08/03/2018
*/

#include <iomanip>
#include "item_table.h"

Item_Table::Item_Table(unsigned table_size)
    : _table(table_size) {}

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
    std::cout << "\t\tHASH TABLE DIAGNOSTICS\n" << SString(57, '=')
              << "\nITEMS:    \t" << _table.size()
              << "\nLOAD FACTOR:\t" << std::setprecision(3) << std::fixed 
              << _table.load_factor() * 100 << '%' << "\nBUCKETS:\t" 
              << _table.buckets() << "\nBUCKETS USED:\t"
              << _table.buckets_in_use() << "\nDATA SPREAD:\t" 
              << std::setprecision(3) << std::fixed << _table.spread() * 100 
              << '%' << "\nLARGEST BUCKET:\t"<< _table.largest_bucket() 
              << " items" << "\nAVERAGE BUCKET:\t" << _table.average_bucket() 
              << " items" << '\n' << SString(57, '=');
    return;
}

