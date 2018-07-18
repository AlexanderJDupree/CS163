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

    size_type* _size; // The shared size of the allocated data
    size_type* _ref_count; // The number of references to the data
    pointer   _data; // The shared data object

  private:

    // Releases the data. This will delete the data, ref count and size for ALL
    // referenced objects
    void release();

};

#include "rc_manager.cpp"

#endif // RC_MANAGER_H

