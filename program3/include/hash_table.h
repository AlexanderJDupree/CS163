/*
File: hash_table.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef> // NULL
#include <exception> // std::exception

template <class K>
struct hash
{
    unsigned long operator()(const K& key) const
    {
        return (key * 7109) * 9743;
    }
};

template <>
struct hash<const char *> 
{
    unsigned long operator()(const char* key) const
    {
        unsigned long hash = (*(const unsigned long*)key) << 2;
        
        return (hash *= 7109) + 9743;
    }

};

template <class K, class V, class F = hash<K> > 
class hash_table
{
  // Forward Declaration
  class hash_node;

  public:
    
    class const_forward_iterator;
    class forward_iterator;

    typedef K                      key_type;
    typedef V                      value_type;
    typedef F                      hasher;
    typedef unsigned               size_type;
    typedef hash_node*             bucket;
    typedef hash_table             self_type;
    typedef forward_iterator       iterator;
    typedef const_forward_iterator const_iterator;

    /****** CONSTRUCTORS ******/

    // Initializes the hash table to the specified bucket size.
    hash_table(unsigned buckets = 11);

    // Range Based Constructor
    template <class key_iterator, class val_iterator>
    hash_table(key_iterator key_begin, key_iterator key_end,
               val_iterator val_begin, val_iterator val_end, 
               unsigned buckets = 11);

    // Clears bucket, deletes the hash table
    ~hash_table();

    /****** MODIFIERS ******/
    
    // Hashes the key, inserts the value to the front of the indexed bucket
    self_type& insert(const K& key, const V& value);

    // Clears each bucket, deletes the hash table
    self_type& clear();


    /****** CAPACITY ******/

    // Returns true if the size is 0
    bool empty() const;

    // Returns the number of elements in the array
    size_type size() const;

    // Returns the number of buckets the table can hold
    size_type buckets() const;

    /****** ITERATOR ACCESS ******/

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;


  private:

    class hash_node
    {
      public:

        typedef hash_node self_type;

        // Default constructor
        hash_node(const K& key = K(), const V& value = V(), hash_node* next = NULL);
        
        // Mutators
        self_type& key(const K& key);
        self_type& value(const V& value);
        self_type& next(const hash_node* next);
        hash_node*& next();
        value_type& value();

        // Inspectors
        const key_type& key() const;
        const value_type& value() const;

      private:

        K _key;
        V _value;
        hash_node* _next;
    };

    unsigned _size; // The number of items in the table
    unsigned _bucket_count; // The max number of buckets the table can hold
    bucket* _buckets; // Dynamic array of buckets, this is the table
    hasher _hash; // Hash function object
    value_type _null_object; // null object pattern, returned on failed searches

    /****** SUBROUTINES ******/

    // Allocates new table, initializes each bucket to null
    void initialize_buckets();
    
    // Pushes new element to the front of a chain
    void push_front(bucket& head, const K& key, const V& value);

    // Clears each element in a buckets chain
    void clear_bucket(bucket& current);

  public:

    /****** ITERATORS ******/

    class const_forward_iterator
    {
      public: 

        typedef const_forward_iterator self_type;

        // Default Constructor
        const_forward_iterator(bucket* begin = NULL, bucket* end = NULL);

        // Increment Operators
        self_type& operator++();
        self_type& operator++(int);

        // Dereference Operators
        const value_type& operator*() const;
        const value_type* operator->() const;

        // Key/Value access
        const key_type& key() const;
        const value_type& value() const;

        // Null check 
        bool null() const;

        // Equality operators
        bool operator==(const self_type& rhs) const;
        bool operator !=(const self_type& rhs) const;

      protected:

        bool next_bucket();
        void throw_if_null() const;

        bucket* _bucket;
        bucket* _end_bucket;
        hash_node* _ptr;

    };

    class forward_iterator : public const_forward_iterator
    {
      public:
        typedef forward_iterator self_type;

        // Default constructor
        forward_iterator(bucket* begin = NULL, bucket* end = NULL)
            : const_forward_iterator(begin, end) {}

        // Dereference Operators
        value_type& operator*();
        value_type* operator->();

        // Key/Value access
        value_type& value(); 

      private:

        void throw_if_null() const;
    };

    // Custom Exception for Iterator class
    struct invalid_iterator : public std::exception
    {
        const char* _error;

        invalid_iterator(const char* error = "invalid iterator: points to NULL")
            : _error(error) {}
        
        const char* what() const throw()
        {
            return _error;
        }

    };

};

#include "hash_table.cpp"

#endif // HASH_TABLE_H


