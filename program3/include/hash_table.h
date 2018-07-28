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

//        KEY      VALUE    HASH FUNCTION
template <class K, class V, class F = hash<K> > 
class hash_table
{
  class hash_node;

  public:
    

    typedef K           key_type;
    typedef V           value_type;
    typedef F           hasher;
    typedef unsigned    size_type;
    typedef hash_node*  bucket;

    hash_table(unsigned buckets = 11);

    bool empty();
    size_type size();
    size_type buckets();

  private:

    class hash_node
    {
      public:

        hash_node(const K& key = K(), const V& value = V(), hash_node* next = NULL)
            : K(key), V(value), next(next) {}

      private:

        K _key; 
        V _value;

        hash_node* next;
    };

    unsigned _bucket_count;
    bucket* _buckets;

};

#include "hash_table.cpp"

#endif // HASH_TABLE_H


