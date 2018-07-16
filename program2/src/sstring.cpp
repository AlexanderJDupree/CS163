/*
File: string.cpp

Description: Implementation file for the SString class. Defines methods for 
             construction, copy assignment, comparison, inspection, and 
             iteration for the underlying char array. 

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 06/27/2018
*/

#include "sstring.h"

SString::SString(const_pointer str) 
    : reference_manager(len(str) + 1), _length(*_size - 1)
{
    if (!catch_null_exception(str))
    {
        copy(str);
    }
    else
    {
        _data[0] = '\0';
    }
}

SString::SString(const self_type& origin)
    : reference_manager(origin), _length(origin._length) {}

SString::~SString() {}

SString::size_type SString::len(const_pointer str)
{
    if (catch_null_exception(str))
    {
        return 0;
    }

    size_type length;

    // Counts the number of characters before null terminator
    for(length = 0; str[length] != '\0'; ++length);

    return length;
}

void SString::copy(const_pointer source)
{
    validate_pointer(source);

    size_type index = 0;
    for(; source[index] != '\0' && index < _length; ++index)
    {
        _data[index] = source[index];
    }

    _data[_length] = '\0';

    return;
}

SString::size_type SString::length() const
{
    return _length;
}

bool SString::empty() const
{
    return _length == 0;
}

bool SString::compare_equal(const self_type& str) const
{
    // Strings are different sizes, they are not the same
    if (_length != str._length)
    {
        return false;
    }
    // Strings are both empty, or they share the same data
    if ((_length == 0 && str._length == 0) || _data == str._data)
    {
        return true;
    }

    // Iterate through each string and compare characters
    return *this == str._data;
}

SString::const_iterator SString::begin() const
{
    return _data;
}

SString::const_iterator SString::end() const
{
    return &_data[_length];
}

void SString::validate_pointer(const_pointer str)
{
    if (str) 
    {
        return;
    }

    throw std::invalid_argument("char pointer points to null");
}

bool SString::catch_null_exception(const_pointer str)
{
    try
    {
        validate_pointer(str);
        return false;
    }
    catch(const std::invalid_argument& err)
    {
        return true;
    }
}

/* Operator Overloads */
SString::self_type& SString::operator=(const SString& str)
{
    // Utilize the copy constructor to create a copy of the string
    SString copy(str);

    // Swap ownership of resources with the copy
    swap(*this, copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

SString::self_type& SString::operator=(const_pointer str)
{
    validate_pointer(str);

    *this = SString(str);

    return *this;
}

void SString::swap(SString& new_string, SString& old_string)
{
    using std::swap;

    swap(new_string._data, old_string._data);
    swap(new_string._length, old_string._length);
    swap(new_string._size, old_string._size);
    swap(new_string._ref_count, old_string._ref_count);
    return;
}

std::ostream& operator << (std::ostream& os, const SString& str)
{
    os << str._data;
    return os;
}

std::istream& operator >> (std::istream& is, SString& str)
{
    char* buffer = new char[100];

    is.get(buffer, 100);

    // We use the assignment operator to handle the buffer copy
    str = buffer;

    delete [] buffer;

    return is;
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
    return lhs.compare_equal(rhs);
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
