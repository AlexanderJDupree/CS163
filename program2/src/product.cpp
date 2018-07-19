/*
File: product.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "product.h"


Product::Product(const string& store, const string& model, unsigned price)
    : _store(store), _model(model), _price(price), _features(Features()) {}

const SString& Product::store() const
{
    return _store;
}

const SString& Product::model() const
{
    return _model;
}

unsigned Product::price() const
{
    return _price;
}

unsigned Product::matches() const
{
    return _features.size();
}

Product& Product::add_match(const string& feature)
{
    _features.push_back(feature);
    return *this;
}

bool Product::operator==(const self_type& rhs) const
{
    return _model == rhs._model;
}

bool Product::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

std::ostream& operator << (std::ostream& os, const Product& product)
{
    os << "\nSTORE:\t" << product._store << "\nMODEL:\t" << product._model 
       << "\nPRICE:\t" << product._price << "\n\nMatched Features: " 
       << product.matches() << "\n============================\n";
    Product::Features::const_iterator it;
    for (it = product._features.begin(); it != product._features.end(); ++it)
    {
        os << *it << '\n';
    }
    os << "============================\n";

    return os;
}

