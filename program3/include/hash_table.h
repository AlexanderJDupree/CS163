/*
File: 

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef> // NULL

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
    

    typedef K           key_type;
    typedef V           value_type;
    typedef F           hasher;
    typedef unsigned    size_type;
    typedef hash_node*  bucket;
    typedef hash_table  self_type;

    /****** CONSTRUCTORS ******/
    hash_table(unsigned buckets = 11);


    /****** MODIFIERS ******/
    self_type& insert(const K& key, const V& value);

    self_type& clear();


    /****** CAPACITY ******/
    bool empty();
    size_type size();
    size_type buckets();

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

        // Inspectors
        const K& key() const;
        const V& value() const;
        const hash_node* next() const;

      private:

        K _key; 
        V _value;
        hash_node* _next;
    };

    unsigned _size;
    unsigned _bucket_count;
    bucket* _buckets;
    hasher _hash;

    /****** SUBROUTINES ******/
    void push_front(bucket& head, const K& key, const V& value);

};

#include "hash_table.cpp"

#endif // HASH_TABLE_H


