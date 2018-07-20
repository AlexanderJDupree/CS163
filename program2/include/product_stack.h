/*
File: product_stack.h

Brief: The Product_Stack is the implementation of a Stack ADT utilizing a 
       linear linked list arrays as the underlying data structure. Each node in 
       the LLL contains a dynamic array of 5 products, when that array is filled
       another node with a dynamic array is instantiated. 

       The Product_Stack comes equipped with methods for construction, push and
       pop, and inspection of the top and bottom of the stack as well as a 
       display method to display the contents of the stack in chronological 
       order.

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#ifndef PRODUCT_STACK_H
#define PRODUCT_STACK_H

#include "linked_list.h"
#include "product.h"

class Product_Stack
{
  public:

      typedef Product_Stack self_type;
      typedef linear_linked_list<Product*> stack;
      
      // Instantiates an empty stack
      Product_Stack();

      // Calls clear_stack()
      ~Product_Stack();

      // Adds a product to the top of the stack
      self_type& push(const Product& product);

      // Decrements the top pointer, deleting nodes if necessary
      self_type& pop();

      // Calls pop, overwirtes product with the current stack pointers data
      Product& pop(Product& product);

      // Peeks the top element, throws if empty
      const Product& top() const;

      // Peeks the bottom of the stack, throws if empty
      const Product& bottom() const;

      // Returns true if the stack is empty
      bool empty() const;

      // Returns the number of items on the stack
      unsigned size() const;

      // Visits each node deleting the allocated array then deletes each node
      void clear_stack();

      // Displays each item on the stack
      void display() const;

  private:

      // Max number of products for the flex array
      static const unsigned MAX_PRODUCTS = 5;

      stack _products; // LLL of Product arrays

      Product* _top; // stack pointer to the index where new data will be pushed
      Product* _end; // Points to the end of the current flex array

      void add_node(); // Adds a new node with an allocated product array

      void remove_node(); // Deletes the top node, updates top and end 

};

#endif // PRODUCT_STACK_H


