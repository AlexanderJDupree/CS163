/*
File: product_stack.h

Brief:

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
      
      Product_Stack();

      ~Product_Stack();

      self_type& push(const Product& product);

      const Product& top() const;

      const Product& bottom() const;

      bool empty() const;

      void clear_stack();

  private:

      static const unsigned MAX_PRODUCTS = 5;

      stack _products;

      Product* _top;
      Product* _end;

      void add_node();

};

#endif // PRODUCT_STACK_H


