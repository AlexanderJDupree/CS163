/*
File: iterator.cpp

Description: 
    Implementation file for the forward_iterator class

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef ITERATOR_CPP
#define ITERATOR_CPP

#include "iterator.h"

template <typename T>
forward_iterator<T>::forward_iterator() : node(NULL) {}

template <typename T>
forward_iterator<T>::forward_iterator(pointer ptr) : node(ptr) {}

/* Operator Overloads */
template <typename T>
forward_iterator<T>& forward_iterator<T>::operator++()
{
    // reassign node member to point to the next element in the container
    node = node->next;
    return *this;
}

template <typename T>
forward_iterator<T>& forward_iterator<T>::operator++(int)
{
    // Create a copy to satisfy postfix incrementation requirements
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
typename forward_iterator<T>::reference
forward_iterator<T>::operator*()
{
    return node->data;
}

template <typename T>
typename forward_iterator<T>::const_reference 
forward_iterator<T>::operator*() const
{
    return node->data;
}

template <typename T>
bool forward_iterator<T>::operator==(const self_type& rhs) const
{
    // Compare memory addresses, NOT the value of the data member
    return node == rhs.node;
}

template <typename T>
bool forward_iterator<T>::operator!=(const self_type& rhs) const
{
    // return the logical NOT of the equality comparison
    return !(*this == rhs);
}

#endif // ITERATOR_CPP