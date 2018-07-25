/*
File: product.h

Brief: Product is a utility class that stores information related to a computer
       for later evaluation. Product class comes equipped with inspectors for
       each attribute, default and value constructors, and out stream operator
       overloads.

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

    /* Since the Product class does not manage any resources, there is no need
     * to specialize a copy constructor, destructor, and assignment operator */
    
    // Inspectors
    const string& store() const;
    const string& model() const;
    unsigned price() const;
    unsigned matches() const;

    // Mutators
    self_type& store(const string& store);
    self_type& model(const string& model);
    self_type& price(const unsigned& price);

    // Adds a matched feature to the feature list
    self_type& add_match(const string& feature);

    // Clears the matched features
    void clear_matches();

    // Comparison operators use the _model attribute for comparison
    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;

    friend std::ostream& operator << (std::ostream& os, const Product& product);

  private:

    string _store; // The store this computer is located at
    string _model; // The model of the computer, used for comparison

    unsigned _price; // The price of the computer

    Features _features; // A list of matched features
};

#endif // PRODUCT_H
