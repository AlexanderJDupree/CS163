/*
File: product_stack.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include "product_stack.h"

Product_Stack::Product_Stack() 
    : _products(stack()), _top(NULL), _end(NULL) {}

Product_Stack::~Product_Stack()
{
    clear_stack();
}

Product_Stack& Product_Stack::push(const Product& product)
{
    if(!_top || _top == _end)
    {
        add_node();
    }

    *_top = product;
    ++_top;

    return *this;
}

void Product_Stack::add_node()
{
    _products.push_front(new Product[MAX_PRODUCTS]);
    _top = _products.front();
    _end = _top + MAX_PRODUCTS;
    return;
}

const Product& Product_Stack::top() const
{
    if(!_top)
    {
        throw std::logic_error("Unable to access top, stack is empty");
    }

    return *(_top - 1);
}

const Product& Product_Stack::bottom() const
{
    if(!_top)
    {
        throw std::logic_error("Unable to access bottom, stack is empty");
    }

    return *_products.back();
}

bool Product_Stack::empty() const
{
    return !(_top);
}

void Product_Stack::clear_stack() 
{
    for (stack::iterator it = _products.begin(); it != _products.end(); ++it)
    {
        delete [] *it;
    }

    _products.clear();

    _top = NULL;
    _end = NULL;

    return;
}
