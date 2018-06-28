/*
File: iterator.h

Description: 
    forward_iterator class is an abstraction of the Node pointer. To "hide" the
    the implementation of the underlying data structure it was required to create
    a class that could abstract the node struct so that a user could traverse 
    the list without needing to access the node member.

    forward_iterator provides methods for default and value based construction. 
    as well as equality/inequality comparisons, dereferencing, and postfix and
    prefix incrementation.

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>

// Forward declaration
template <typename T> class Sorted_List;

template <typename T>
class forward_iterator
{
  public:
    /* Type definitions */
    typedef typename T::value_type      value_type;
    typedef typename T::reference       reference;
    typedef typename T::const_reference const_reference;
    typedef typename T::pointer         pointer;
    typedef typename T::const_pointer   const_pointer;
    typedef forward_iterator            self_type;

    /* Constructors */

    /// @brief: default constructor points node to NULL
    forward_iterator();

    /** 
    @brief: value constructor points node to ptr's value
    @param: ptr is a pointer to a data type T
    */
    forward_iterator(pointer ptr);

    /* Operator Overloads */

    /**
    @brief: prefix increment operator modifies node to point the next node in 
            a list
    @return: Returns self reference so this operation can be chained with other
             methods
    */
    self_type& operator++(); // Prefix ++

    /**
    @brief: postfix increment operator makes a COPY of itself and then calls 
            the prefix increment operator to modify it's state
    @return: Returns a COPY of itself before incrementation
    */
    self_type& operator++(int); // Postfix ++

    /**
    @brief: * operator allows the user to inspect and mutate the data member of
            node
    @return: returns a read/write reference to the data member of a node
    */
    reference operator*();

    /**
    @brief: for const qualified iterators, the * operator allows the user to 
            inspect and/or copy the value of the data member
    @return: returns a read only reference to the data member of a node
    */
    const_reference operator*() const;

    /**
    @brief: tests to see if each iterator is pointing to the same memory address
    @param: rhs is an iterator to be used for comparison
    @return: returns true of both rhs and this are pointing to the same address
    */
    bool operator==(const self_type& rhs) const;

    /**
    @brief: returns the logical not of the equality comparison
    @param: rhs is an iterator to be used for comparison
    */
    bool operator!=(const self_type& rhs) const;

    /* 
    Because the iterator is designed to abstract a private 
    member of the sorted list class, it is safe to make it a friend so that
    we can acces the node member when desired.
    */
    friend class Sorted_List<T>;
   
  protected:
    pointer node;

};

/*
Because this is a templated class, we need to include the implementation in 
the header file so the compiler can instantiate the methods with the right type 
*/
#include "iterator.cpp"

#endif // ITERATOR_H