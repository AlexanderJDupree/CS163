/*
File: hash_table.h

Brief: This implementation of the hash table data structure is fully templated
       and can be instantiated with specialized hash functions. For the best 
       runtime efficiency of this structure it is recommended to specialize a
       hash functor object for your data set, as well as instantiate this hash
       table with a large prime number to decrease the load factor and reduce
       the chance of collision

       This hash table utilizes seperate chaining to handle collisions. As the
       load factor grows, the chains will grow larger, reducing runtime 
       efficiency.

       This hash table is implemented with functions to insert, remove, erase, 
       find, and iterate over elements stored onto the table. It also comes with
       functions to display diagnostic data, such as the load factor, 
       the largest bucket, and average chain length.


Author: Alexander DuPree

Class: CS163

Assignment: program3

Date: 08/03/2018
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef> // NULL
#include <exception> // std::exception
#include <algorithm> // std::swap

template <class K>
struct hash
{
    unsigned long operator()(const K& key) const
    {
        unsigned long hash = (unsigned long)key;
        for (unsigned i = 0; i < hash % 11; ++i)
        {
            hash = (hash * 9743) << i;
        }
        return hash;
    }
};

template <>
struct hash<const char *> 
{
    // String specialization of the hash function
    unsigned long operator()(const char* key) const
    {
        // 1202nd prime number. This was selected arbitrarly.
        unsigned long hash = 9743;
        for(unsigned i = 0; key[i] != '\0'; ++i)
        {
            // Bit shift left the key's representation and xor it
            hash *= hash ^ (*(const unsigned long*)key + i) << 5;
        }

        return hash;
    }
};

template <class K, class V, class F = hash<K> > 
class hash_table
{
  // Forward Declaration
  class hash_node;

  public:
    
    class const_forward_iterator;
    class const_bucket_iterator;
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

    // Copy Constructor
    hash_table(const self_type& origin);

    // Clears buckets, deletes the hash table
    ~hash_table();

    /****** MODIFIERS ******/
    
    // Hashes the key, inserts the value to the front of a bucket
    self_type& insert(const key_type& key, const value_type& value);

    // Hashes the key, removes element with the matching key
    bool erase(const key_type& key);

    // Clears each bucket, deletes the hash table
    self_type& clear();

    // Getters and setters for the default object, default object reference is
    // returned on failed searches.
    self_type& default_object(const value_type& obj);
    const value_type& default_object() const;
    value_type& default_object();

    /****** OPERATIONS ******/

    // Returns the value for the matching key, or the default object
    value_type& find(const key_type& key);
    const value_type& find(const key_type& key) const;

    /****** CAPACITY ******/

    // Returns true if the size is 0
    bool empty() const;

    // Returns the number of elements in the array
    size_type size() const;

    // Returns the number of buckets the table can hold
    size_type buckets() const;

    /****** DIAGNOSTICS ******/

    // Load factor is size / buckets
    float load_factor() const;

    // Spread is the number of buckets in use / number of buckets
    float spread() const;

    // Counts the number of buckets in use
    unsigned buckets_in_use() const;

    // Returns the length of the longest chain
    unsigned largest_bucket() const;

    // Returns the average chaing length
    unsigned average_bucket() const;

    // Higher order function that will increment a counter when a predicate is 
    // fulfilled
    template <class InputIterator, class Predicate>
    unsigned count_if(InputIterator begin, InputIterator end, Predicate pred) const;

    /****** ITERATOR ACCESS ******/

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    /****** OPERATORS ******/

    // Element Access Operator
    value_type& operator[](const key_type& key);
    const value_type& operator[](const key_type& key) const;

    // Equality/Comparison operators
    bool operator==(const self_type& rhs) const;
    bool operator!=(const self_type& rhs) const;

    /****** COPY ASSIGNMENT AND SWAP ******/

    // Creates a copy of the origin, swaps ownership with the copy
    self_type& operator=(const self_type& origin);

    // Swaps pointers to each other's resources, reassigning ownership.
    static void swap(self_type& new_table, self_type& old_table);

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
    value_type _default_object; // null object pattern, returned on failed searches

    /****** SUBROUTINES ******/

    // Allocates new table, initializes each bucket to null
    void initialize_buckets();
    
    // Pushes new element to the front of a chain
    void push_front(bucket& head, const K& key, const V& value);

    // Clears each element in a buckets chain
    void clear_bucket(bucket& current);

    // Deletes the node matching the search key
    bool erase(hash_node*& current, const key_type& key);

    /****** Functors ******/
    struct null_bucket
    {
        bool operator()(bucket* head) const
        {
            return *head != NULL;
        }
    };

    struct count_nodes
    {
        bool operator()(const const_bucket_iterator it) const
        {
            return !it.null();
        }
    };

  public:

    /****** ITERATORS ******/
    // Buckets iterator iterates through the LLL contained in a bucket. Does
    // not find the next bucket when it reaches NULL
    class const_bucket_iterator
    {
      public:
        typedef const_bucket_iterator self_type;

        // Default constructor
        const_bucket_iterator(hash_node* ptr = NULL)
            : _ptr(ptr) {}

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
        bool operator!=(const self_type& rhs) const;

      protected:

        void throw_if_null() const; 

        hash_node* _ptr;
    };

    // Forward Iterator iterates through the entire container, and will find the
    // next valid bucket to iterate when it reaches the end of a chain
    class const_forward_iterator : public const_bucket_iterator
    {
      public: 

        typedef const_forward_iterator self_type;

        // Default Constructor
        const_forward_iterator(bucket* begin = NULL, bucket* end = NULL);

        // Increment Operators
        self_type& operator++();
        self_type& operator++(int);

      protected:

        bool next_bucket();
        void throw_if_null() const;

        bucket* _bucket;
        bucket* _end_bucket;
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


