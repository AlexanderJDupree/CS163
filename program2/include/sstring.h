/*
File: sstring.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
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

    /* Constructors */

    // c-string constructor
    SString(const_pointer str = NULL);

    // Copy constructor copies each character from origins buffer onto it's 
    // buffer.
    SString(const self_type& origin);

    // Destructor deletes the block of memory containing the string
    ~SString();

    // len counts the number of characters in a cstring before null character
    static size_type len(const_pointer str);

    /* Capacity Functions */
    // Returns the number of characters in the string
    size_type length() const;

    // Tests if the string is empty;
    bool empty() const;

    // Compares string length first, then compares the cstring
    bool compare_equal(const self_type& str) const;

    /* Iterators */

    // returns a random-access iterator to the beginning of the string
    const_iterator begin() const;

    // returns a random-access iterator to the null character of the string
    const_iterator end() const;

    // Swaps ownership of resources
    static void swap(SString& new_string, SString& old_string);

    /* Operator Overloads */

    // Makes a copy of str, swaps resource ownership with the copy,
    // copy destructs with the old data when it goes out of scope
    self_type& operator=(const SString& str);
    self_type& operator=(const_pointer str);

    friend std::ostream& operator<<(std::ostream& os, const self_type& str);
    friend std::istream& operator>>(std::istream& is, self_type& str);

    // Comparison operators uses std::strcmp to compare for equality
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

  private:

    // Throws an exception if the pointer is NULL
    static void validate_pointer(const_pointer);
    
    // Returns true if a null exception was thrown
    static bool catch_null_exception(const_pointer);
    
    // copies each character from source including null character. Stops 
    // copying if the buffer is full
    void copy(const_pointer source);
};

#endif // STRING_H

