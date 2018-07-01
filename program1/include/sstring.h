/*
File: string.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <ostream>

class SString 
{
  public:
    typedef SString      self_type;
    typedef char        value_type;
    typedef char&       reference;
    typedef const char& const_reference;
    typedef char*       pointer;
    typedef const char* const_pointer;
    typedef size_t      size_type;
    typedef char*       iterator;
    typedef const char* const_iterator;

    /* Constructors */

    // Default constructor sets the buffer size of short string to 100 chars,
    // throws std::bad_alloc if size is not a positive integer
    SString(size_type size = 100);

    // C-string consructor initializes a string to the value of the c-string
    // If str is larger than the buffer, only n characters from str will be 
    // copied
    SString(const_pointer str, size_type size = 100);

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

    /* Iterators */
    // returns a random-access iterator to the beginning of the string
    iterator begin();
    const_iterator begin() const;

    // returns a random-access iterator to the null character of the string
    iterator end();
    const_iterator end() const;

    // Swaps ownership of resources
    static void swap(SString& new_string, SString& old_string);

    /* Operator Overloads */

    // Makes a copy of str, swaps resource ownership with the copy,
    // copy destructs with the old data when it goes out of scope
    self_type& operator=(const SString& str);

    friend std::ostream& operator<<(std::ostream& os, const self_type& str);

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

};

#endif // STRING_H

