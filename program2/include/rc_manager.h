/*
File: rc_manager.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#ifndef RC_MANAGER_H
#define RC_MANAGER_H

#include <cstddef> // NULL

template <typename T> 
class reference_manager
{
  public:
    
    typedef T                   value_type;
    typedef T&                  reference; 
    typedef T*                  pointer;
    typedef const T&            const_reference;
    typedef const T*            const_pointer;
    typedef reference_manager   self_type;
    typedef unsigned            size_type;

    reference_manager(size_type size = 0);

    reference_manager(const self_type& origin);

    virtual ~reference_manager();

    // Returns the number of elements in the array
    size_type size() const;

    // Returns the number of references to the array
    size_type ref_count() const;

  protected:

    size_type* _size;
    size_type* _ref_count;
    pointer   _data;

    void release();

};

#include "rc_manager.cpp"

#endif // RC_MANAGER_H

