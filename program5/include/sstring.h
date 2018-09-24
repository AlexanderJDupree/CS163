/*
File: sstring.h

Brief: The Shared String is an immutable reference counted string. These
       characteristics provides many benefits. Namely, this class negates 
       the costs of copies, as any object requiring the strings data can just 
       reference the string and have that data accessible; And because the data 
       is immutable we can be confident that no matter how many references the 
       string has, the underlying data will not change for any referencing object.

       Shared Strings can be reassigned but they cannot be modified. When a 
       reassignment happens to another shared string then the original reference
       count is decremented and the new reference count is incremented. When the
       Shared String is reassigned to a string literal or a cstring, then the 
       string becomes unique, and allocates the required space for the string.

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/11/2018
*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <stdexcept> 
#include "rc_manager.h"

// SString inherits the functionality of the reference manager to allow for 
// smart allocation, copy, and deallocation
class SString : public reference_manager<char>
{
  public:

    typedef SString     self_type;
    typedef char*       pointer;
    typedef const char& const_reference;
    typedef const char* const_pointer;
    typedef size_t      size_type;
    typedef const char* const_iterator;

    /****** CONSTRUCTORS ******/

    // Default construction
    SString();

    // c-string constructor
    SString(const_pointer str);

    // Sub-string constructor
    SString(pointer begin, pointer end);

    // Fill constructor
    SString(unsigned n, char fill);

    // Copy Constructor increments reference count
    SString(const self_type& origin);

    ~SString();

    /****** CAPACITY ******/

    // Returns the number of characters in the string
    size_type length() const;

    // Tests if the string is empty;
    bool empty() const;

    // len counts the number of characters in a cstring before null character
    static size_type len(const_pointer str);

    /****** OPERATIONS ******/
    
    // Returns a copy of the string from [begin:end]
    self_type substring(unsigned begin=0, unsigned end=0) const;

    // Returns a substring of the string from (0, width)
    self_type truncate(unsigned width = 8) const;

    /****** ITERATORS ******/

    // returns a random-access iterator to the beginning of the string
    const_iterator begin() const;

    // returns a random-access iterator to the null character of the string
    const_iterator end() const;

    /****** COPY AND SWAP ******/

    self_type& operator=(const self_type& str);
    self_type& operator=(const_pointer str);

    // Swaps ownership of resources
    static void swap(SString& new_string, SString& old_string);

    /****** CONCATENATION ******/

    friend self_type operator+(const self_type& lhs, const_pointer rhs);
    friend self_type operator+(const_pointer lhs, const self_type& rhs);
    friend self_type operator+(const self_type& lhs, const self_type& rhs);

    /****** STREAM OPERATORS ******/

    friend std::ostream& operator<<(std::ostream& os, const self_type& str);
    friend std::istream& operator>>(std::istream& is, self_type& str);

    /****** COMPARISON OPERATORS ******/

    // Comparison operators uses std::strcmp to compare for equality
    // Compares string length first, then compares the cstring
    bool compare_equal(const self_type& str) const;

    // Comparison operators are freestanding, allowing for comparison of
    // cstrings and SStrings on either side of the operator
    friend bool operator==(const self_type& lhs, const_pointer rhs);
    friend bool operator==(const_pointer lhs, const self_type& rhs);
    friend bool operator==(const self_type& lhs, const self_type& rhs);

    friend bool operator!=(const self_type& lhs, const_pointer rhs);
    friend bool operator!=(const_pointer lhs, const self_type& rhs);
    friend bool operator!=(const self_type& lhs, const self_type& rhs);

    friend bool operator< (const self_type& lhs, const_pointer rhs);
    friend bool operator< (const_pointer lhs, const self_type& rhs);
    friend bool operator< (const self_type& lhs, const self_type& rhs);

    friend bool operator> (const self_type& lhs, const_pointer rhs);
    friend bool operator> (const_pointer lhs, const self_type& rhs);
    friend bool operator> (const self_type& lhs, const self_type& rhs);

    /****** TYPE CASTS ******/
    operator const char*() const { return _data; }
    operator const unsigned long*() const { return (const unsigned long*)_data; }

  private:

    /****** SUBROUTINES ******/

    // Throws an exception if the pointer is NULL
    static void validate_pointer(const_pointer);
    
    // Returns true if a null exception was thrown
    static bool catch_null_exception(const_pointer);
    
    // copies each character from source including null character. Stops 
    // copying if the buffer is full
    void copy(const_pointer source);
};

struct invalid_substring : public std::exception
{
    const char * _error;

    invalid_substring(const char* err)
        : _error(err) {}

    const char* what() const throw()
    {
        return _error;
    }
};
#endif // STRING_H

