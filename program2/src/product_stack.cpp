/*
File: product_stack.h

Brief: Implementation file for the Product_Stack ADT. Defines methods for 
       push, pop, peek, and display

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
    // Stack is empty or array is full
    if(!_top || _top == _end)
    {
        add_node();
    }

    *_top = product;
    ++_top;

    return *this;
}

Product_Stack& Product_Stack::pop()
{
    if (!_top) // Stack is empty, can't pop
    {
        return *this;
    }

    // Roll the top pointer back one element, deleting nodes if necessary
    if(_top == _products.front())
    {
        remove_node();
    }
    else
    {
        --_top;
    }

    return *this;
}

Product& Product_Stack::pop(Product& product)
{
    // Rolls the top pointer back one element
    pop();

    // The "popped product" is now where top is indexed
    product = *_top;

    return product;
}

void Product_Stack::add_node()
{
    // Allocate new flex array
    _products.push_front(new Product[MAX_PRODUCTS]);

    _top = _products.front();
    _end = _top + MAX_PRODUCTS;
    return;
}

void Product_Stack::remove_node()
{
    // Delete the flex array
    delete [] _products.front();
    // Delete the node
    _products.pop_front();

    // Set top to the top of the previous node
    _end = _products.front() + MAX_PRODUCTS;
    _top = _end - 1;
    return;
}

const Product& Product_Stack::top() const
{
    if(!_top)
    {
        throw std::logic_error("Unable to access top, stack is empty");
    }

    if(_top == _products.front())
    {
        // If the top pointer is at the first element of the front node that 
        // means the last element pushed is the last element of the next node.
        // So this line here is to dereference the last element of the next node.
        return *(*(++_products.begin()) + (MAX_PRODUCTS - 1));
        //         ^^^^^^^^^^^^^^^^^^^     ^^^^^^^^^^^^^^^^
        //         increment iterator      get address of last element
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

unsigned Product_Stack::size() const
{
    // Size is the number of nodes times the number of products per node minus
    // the difference of the top pointer and the end of the array
    return _products.size() * MAX_PRODUCTS - (_end - _top);
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

void Product_Stack::display() const
{
    std::cout << "\n\t\t\tCOMPUTERS\n"
                 "==========================================================\n"
                 "Saved Computers: " << size() << '\n';
    if(!_top)
    {
        return;
    }
    
    Product* temp = _top;
    stack::const_iterator node = _products.begin();

    while(temp != _products.back())
    {
        if (temp == *node)
        {
            temp = *(++node) + MAX_PRODUCTS;
        }

        --temp;
        std::cout << *temp << std::endl;
    }

    return;
}

