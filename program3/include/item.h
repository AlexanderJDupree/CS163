/*
File: item.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef ITEM_H
#define ITEM_H

#include "sstring.h"

class Item
{
  public:

    typedef Item    self_type;
    typedef SString string;

    Item(string name="", string description="", string color="", string website="");

    template <class Container>
    Item(Container container);

    // Inspectors
    const string& name() const;
    const string& description() const;
    const string& color() const;
    const string& website() const;

    // Operator Overloads
    friend std::ostream& operator<<(std::ostream& os, const Item& item);

  private:

    string _name, _description, _color, _website;
};

template <class Container>
Item::Item(Container container)
    : _name(container[0]), _description(container[1]), _color(container[2]), 
      _website(container[3]) {}

#endif // ITEM_H

