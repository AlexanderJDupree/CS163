/*
File: hash_table.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#include "item.h"
#include "hash_table.h"

// String Specialization of the hash function
template <>
struct hash<SString>
{
    unsigned long operator()(const char* key) const
    {
        unsigned long hash = 7109;
        for(unsigned i = 0; i < std::strlen(key); ++i)
        {
            hash *= hash ^ (*(const unsigned long*)key + i) << 2;
        }
        return hash *= 7109;
    }
};

class Item_Table
{
  public:

    typedef SString string;
    typedef hash_table<string, Item> Table;

    // Default Constructor initializes table to 11 buckets
    Item_Table(unsigned table_size = 11);

    // Item_Table ADT does not manage any resouces, the default destructor is used
    ~Item_Table() {}

    void add(const Item& item);

    const Item& retrieve(const SString& name) const;




  private:

    Table table;
};

#endif //ITEM_TABLE_H

