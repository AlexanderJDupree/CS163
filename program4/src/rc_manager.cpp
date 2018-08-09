/*
File: rc_manager.cpp

Brief: Implementation file for the Reference manager garbage collector

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/03/2018
*/

#ifndef RC_MANAGER_CPP
#define RC_MANAGER_CPP

#include "rc_manager.h"

template <typename T>
reference_manager<T>::reference_manager(size_type size)
    : _size(new size_type(size)), 
      _ref_count(new unsigned(1)), 
      _data(new value_type[size]) {}

template <typename T>
reference_manager<T>::reference_manager(const self_type& origin)
    : _size(origin._size), _ref_count(origin._ref_count), _data(origin._data)
{
    ++(*_ref_count);
}

template <typename T>
reference_manager<T>::~reference_manager()
{
    if(--(*_ref_count) == 0)
    {
        release();
    }
}

template <typename T>
unsigned reference_manager<T>::size() const
{
    return *_size;
}

template <typename T>
unsigned reference_manager<T>::ref_count() const
{
    return *_ref_count;
}

template <typename T>
void reference_manager<T>::release()
{
    delete [] _data;
    delete _size;
    delete _ref_count;

    _size = NULL;
    _ref_count = NULL;
    _data = NULL;
}

#endif // RC_ARRAY_CPP

