/*
File: 

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP

#include "hash_table.h"

template <class K, class V, class F>
hash_table<K, V, F>::hash_table(unsigned buckets) 
    : _size(0), _bucket_count(buckets), _buckets(new bucket[_bucket_count]) 
{
    // Ensure each bucket is initialized to NULL
    for (bucket i = _buckets[0]; i != _buckets[_bucket_count]; ++i)
    {
        i = NULL;
    }
}

template <class K, class V, class F>
hash_table<K, V, F>& hash_table<K, V, F>::insert(const K& key, const V& value)
{
    unsigned index = _hash(key) % _bucket_count;

    push_front(_buckets[index], key, value);

    return *this;
}

template <class K, class V, class F>
void hash_table<K, V, F>::push_front(bucket& head, const K& key, const V& value)
{
    if(head)
    {
        bucket temp = new hash_node(key, value, head);
        head = temp;
    }
    else
    {
        head = new hash_node(key, value);
    }

    ++_size;
    return;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::empty()
{
    return _size == 0;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::size()
{
    return _size;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::buckets()
{
    return _bucket_count;
}

/****** HASH NODE CLASS ******/

template <class K, class V, class F>
hash_table<K, V, F>::hash_node::hash_node(const K& key, const V& value, hash_node* next)
    : _key(key), _value(value), _next(next) {}

template <class K, class V, class F>
typename hash_table<K, V, F>::hash_node& 
hash_table<K, V, F>::hash_node::key(const K& key)
{
    _key = key;
    return *this;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::hash_node& 
hash_table<K, V, F>::hash_node::value(const V& value)
{
    _value = value;
    return *this;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::hash_node& 
hash_table<K, V, F>::hash_node::next(const hash_node* next)
{
    _next = next;
    return *this;
}

template <class K, class V, class F>
const K& hash_table<K, V, F>::hash_node::key() const
{
    return _key;
}

template <class K, class V, class F>
const V& hash_table<K, V, F>::hash_node::value() const
{
    return _value;
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::hash_node* 
hash_table<K, V, F>::hash_node::next() const
{
    return _next;
}

#endif // HASH_TABLE_CPP

