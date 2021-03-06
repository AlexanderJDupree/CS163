/*
File: sstring.h

Description: SString (short string) acts as an immutable char buffer. The primary 
             reason for creating this class was to free up the responsibility of
             handling raw char pointers in other ADT's. When handling raw char
             points within a class, the same methods must be written over and 
             over to prevent memory leaks and enable comparison between strings.
             Therefore, creating a simple string class to handle the allocation
             deallocation and comparison of raw char pointers allows other 
             ADT's to focus on a single responsibility.

             The SString class comes equipped with random access iterators, 
             overloaded comparison operators, exception safe copy assignment and
             copy construction, as well as input and output stream overloads.

             By default, the SString is constructed with a 50 character limit. 
             If a string literal or char pointer contains more than 50 characters
             then the string is truncated. Once the string is constructed it 
             cannot be modified. However, it can be reassigned.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>

class SString 
{
  public:
    typedef SString     self_type;
    typedef char        value_type;
    typedef char&       reference;
    typedef const char& const_reference;
    typedef char*       pointer;
    typedef const char* const_pointer;
    typedef size_t      size_type;
    typedef char*       iterator;
    typedef const char* const_iterator;

    /* Constructors */

    // Default constructor sets the buffer size of short string to 50 chars,
    // throws std::bad_alloc if size is not a positive integer
    SString(size_type size = 50);

    // C-string consructor initializes a string to the value of the c-string
    // If str is larger than the buffer, only n characters from str will be 
    // copied
    SString(const_pointer str, size_type size = 50);

    // Copy constructo copies each character from origins buffer onto it's 
    // buffer.
    SString(const self_type& origin);

    // Destructor deletes the block of memory containing the string
    ~SString();

    // len counts the number of characters in a cstring before null character
    static size_type len(const_pointer str);

    // copies each character from source including null character. Stops 
    // copying if the buffer is full
    size_type copy(const_pointer source);

    /* Capacity Functions */
    // Returns the number of characters in the string
    size_type length() const;

    // Returns the size of the character buffer
    size_type capacity() const;

    // Tests if the string is empty;
    bool empty() const;

    // Compares string length first, then compares the cstring
    bool compare_equal(const self_type& str) const;

    /* Iterators */

    // returns a random-access iterator to the beginning of the string
    iterator begin();
    const_iterator begin() const;

    // returns a random-access iterator to the null character of the string
    iterator end();
    const_iterator end() const;

    // Swaps ownership of resources
    static void swap(SString& new_string, SString& old_string);

    // Returns a copy of the string as all lower cased characters
    self_type lower() const;

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

    size_type _capacity; // Max number of characters the string can store

    size_type _length; // Number of characters in the string

    pointer _data; // pointer the start of the cstring array

    static void validate_pointer(const_pointer);
    static bool catch_null_exception(const_pointer);

};

#endif // STRING_H

