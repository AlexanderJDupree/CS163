/*
File: item_table.h

Brief: Item_Table ADT is the abstraction of the hash_table data structure. The
       Item_Table provides methods for adding, removing, and retrieving Item 
       objects. This file also contains a specialiazation of the hash function
       to accompany SString objects.

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 08/03/2018
*/

#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#include "item.h"
#include "hash_table.h"

// String Specialization of the hash function
template <>
struct hash<SString>
{
    unsigned long operator()(const SString& key) const
    {
        // Arbitrary prime number
        unsigned long hash = 9743;

        for(SString::const_iterator it = key.begin(); it != key.end(); ++it)
        {
            // Multiply the hash with the product of the keys ascii value
            hash *= *it * 7109;

            // XOR the hash
            hash = hash ^ 17321;
        }

        return hash;
    }
};

class Item_Table
{
  public:

    typedef SString                  string;
    typedef hash_table<string, Item> Table;
    typedef Table::const_iterator    const_iterator;

    // Default Constructor initializes table to 11 buckets
    Item_Table(unsigned table_size = 11);

    ~Item_Table();

    // Adds the item to the table
    void add(const Item& item);

    // Removes the specified item from the table
    bool remove(const string& item_name);

    // Retrieves the specified item
    const Item& retrieve(const string& item_name) const;

    // Clears each item from the table
    void clear();

    // Returns the number of items on the table
    unsigned size() const;

    const_iterator begin() const;
    const_iterator end() const;

    // Prints the tables diagnostic data
    void display_diagnostics();

  private:

    Table _table;

};

#endif //ITEM_TABLE_H

