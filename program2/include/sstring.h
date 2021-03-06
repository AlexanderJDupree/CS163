/*
File: sstring.h

Brief: SString (Shared String) is a complete rework of the short string class
       I wrote for the last assignment. The short string class I wrote for 
       program 1 was a clunky mess that allocated too much memory as a buffer
       despite the length of the string. Worse yet, it made a lot of copies of 
       the same data. The purpose behind it was to relieve any class that 
       required a string of the extra responsibilities behind allocating, 
       deallocating, and comparing cstrings. 
       
       The Shared String is an immutable reference counted string. These
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

    /****** CONSTRUCTORS ******/

    // c-string constructor
    SString(const_pointer str = NULL);

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

#endif // STRING_H

