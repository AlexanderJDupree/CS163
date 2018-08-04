/*
File: item.h

Brief: Item class is a basic utility class to store information related to a 
       specific item or product. The Item class contains four fields directly
       related to the fields corresponding in the 'Shopping.txt'.

Author: Alexander DuPree

Class: CS163

Assignment: program 3

Date: 08/03/2018
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

    // Mutators
    self_type& name(const string& name);
    self_type& description(const string& description);
    self_type& color(const string& color);
    self_type& website(const string& website);

    // Operator Overloads
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    
    bool operator < (const self_type& rhs) const;
    bool operator > (const self_type& rhs) const;
    bool operator ==(const self_type& rhs) const;
    bool operator !=(const self_type& rhs) const;
    bool operator <=(const self_type& rhs) const;
    bool operator >=(const self_type& rhs) const;

  private:

    string _name, _description, _color, _website;
};

template <class Container>
Item::Item(Container container)
    : _name(container[0]), _description(container[1]), _color(container[2]), 
      _website(container[3]) {}

#endif // ITEM_H

