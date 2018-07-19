/*
File: product.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#ifndef PRODUCT_H
#define PRODUCT_H

#include "sstring.h"
#include "linked_list.h"

class Product
{
  public:

    typedef SString string;
    typedef Product self_type;
    typedef linear_linked_list<string> Features;

    // Default construction
    Product(const string& store="", const string& model="", unsigned price=0);

    const string& store() const;
    const string& model() const;
    unsigned price() const;
    unsigned matches() const;

    self_type& add_match(const string& feature);

    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;

    friend std::ostream& operator << (std::ostream& os, const Product& product);

  private:

    string _store;
    string _model;

    unsigned _price;

    Features _features;

};

#endif // PRODUCT_H
