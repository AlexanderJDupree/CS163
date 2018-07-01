/*
File: string.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "sstring.h"

SString::SString(size_type size) 
    : _capacity(size), _length(0), _data(new char[_capacity]) {}

SString::SString(const_pointer str, size_type size) 
    : _capacity(size), _length(0), _data(new char[_capacity])
{
    _length = copy(str);
}

SString::SString(const self_type& origin)
    : _capacity(origin._capacity), _length(0), _data(new char[_capacity])
{
    _length = copy(origin._data);
}

SString::~SString()
{
    delete [] _data;
    _data = NULL;
}

SString::size_type SString::len(const_pointer str)
{
    validate_pointer(str);

    size_type length;

    // Counts the number of characters before null terminator
    for(length = 0; str[length] != '\0'; ++length);

    return length;
}

SString::size_type SString::copy(const_pointer source)
{
    validate_pointer(source);

    size_type index = 0;
    for(; source[index] != '\0' && index < _capacity - 1; ++index)
    {
        _data[index] = source[index];
    }

    _length = index;
    _data[_length] = '\0';

    return index;
}

SString::size_type SString::length() const
{
    return _length;
}

SString::size_type SString::capacity() const
{
    return _capacity;
}

bool SString::empty() const
{
    return _length == 0;
}

SString::iterator SString::begin()
{
    return _data;
}

SString::const_iterator SString::begin() const
{
    return _data;
}

SString::iterator SString::end()
{
    return &_data[_length];
}

SString::const_iterator SString::end() const
{
    return &_data[_length];
}

void SString::swap(SString& new_string, SString& old_string)
{
    using std::swap;

    swap(new_string._data, old_string._data);
    swap(new_string._length, old_string._length);
    swap(new_string._capacity, old_string._capacity);
    return;
}

void SString::validate_pointer(const_pointer str)
{
    if (str) 
    {
        return;
    }

    throw std::invalid_argument("char pointer points to null");
}

/* Operator Overloads */
SString::self_type& SString::operator=(const SString& str)
{
    // Utilize the copy constructo to create a copy of the string
    SString copy(str);

    // Swap ownership of resrouces with the copy
    swap(*this, copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

std::ostream& operator << (std::ostream& os, const SString& str)
{
    os << str._data;
    return os;
}

bool operator==(const SString& lhs, const char* rhs)
{
    return std::strcmp(lhs._data, rhs) == 0;
}
bool operator==(const char* lhs, const SString& rhs)
{
    return rhs == lhs;
}
bool operator==(const SString& lhs, const SString& rhs)
{
    return lhs == rhs._data;
}
bool operator!=(const SString& lhs, const char* rhs)
{
    return !(lhs == rhs);
}
bool operator!=(const char* lhs, const SString& rhs)
{
    return !(rhs == lhs);
}
bool operator!=(const SString& lhs, const SString& rhs)
{
    return !(lhs == rhs._data);
}
bool operator< (const SString& lhs, const char* rhs)
{
    return std::strcmp(lhs._data, rhs) < 0;
}
bool operator< (const char* lhs, const SString& rhs)
{
    return (rhs < lhs);
}
bool operator< (const SString& lhs, const SString& rhs)
{
    return lhs < rhs._data;
}
bool operator> (const SString& lhs, const char* rhs)
{
    return !(lhs < rhs);
}
bool operator> (const char* lhs, const SString& rhs)
{
    return !(rhs < lhs);
}
bool operator> (const SString& lhs, const SString& rhs)
{
    return !(lhs < rhs._data);
}
