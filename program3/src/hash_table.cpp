/*
File: hash_table.cpp

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
    // Pointer arithmetic is used to reduce operation costs
    for (bucket* i = _buckets; *i != _buckets[_bucket_count]; ++i)
    {
        *i = NULL;
    }
}

template <class K, class V, class F>
template <class key_iterator, class val_iterator>
hash_table<K, V, F>::hash_table(key_iterator key_begin, key_iterator key_end,
                                val_iterator val_begin, val_iterator val_end,
                                unsigned buckets)
    : _size(0), _bucket_count(buckets), _buckets(NULL)
{
    initialize_buckets();
    while (key_begin != key_end && val_begin != val_end)
    {
        insert(*key_begin++, *val_begin++);
    }
}

template <class K, class V, class F>
hash_table<K, V, F>::~hash_table()
{
    clear();

    delete _buckets;
    _buckets = NULL;
}

template <class K, class V, class F>
void hash_table<K, V, F>::initialize_buckets()
{
    if (!_buckets)
    {
        _buckets = new bucket[_bucket_count];
        for (bucket* i = _buckets; *i != _buckets[_bucket_count]; ++i)
        {
            *i = NULL;
        }
    }
    return;
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
hash_table<K, V, F>& hash_table<K, V, F>::clear()
{
    if (empty())
    {
        return *this;
    }

    for (unsigned i = 0; i < _bucket_count; ++i)
    {
        clear_bucket(_buckets[i]);
    }   

    _size = 0;

    return *this;
}

template <class K, class V, class F>
void hash_table<K, V, F>::clear_bucket(bucket& current)
{
    if (!current)
    {
        return;
    }

    clear_bucket(current->next());

    delete current;
    current = NULL;

    return;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::empty() const
{
    return _size == 0;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::size() const
{
    return _size;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::buckets() const
{
    return _bucket_count;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::iterator
hash_table<K, V, F>::begin()
{
    if (empty())
    {
        return iterator(NULL);
    }

    return iterator(_buckets, _buckets + _bucket_count);
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_iterator
hash_table<K, V, F>::begin() const
{
    if (empty())
    {
        return const_iterator(NULL);
    }

    return const_iterator(_buckets, _buckets + _bucket_count);
}

template <class K, class V, class F>
typename hash_table<K, V, F>::iterator
hash_table<K, V, F>::end()
{
    return iterator(NULL);
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_iterator
hash_table<K, V, F>::end() const
{
    return const_iterator(NULL);
}

/****** HASH NODE CLASS ******/

template <class K, class V, class F>
hash_table<K, V, F>::hash_node::hash_node(const K& key, const V& value, hash_node* next)
    : _key(key), _value(value), _next(next) {}

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
typename hash_table<K, V, F>::hash_node*&
hash_table<K, V, F>::hash_node::next()
{
    return _next;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type&
hash_table<K, V, F>::hash_node::value()
{
    return _value;
}

/****** ITERATORS ******/

/* const_forward_iterator */
template <class K, class V, class F>
hash_table<K, V, F>::const_forward_iterator::const_forward_iterator(bucket* begin,
                                                                    bucket* end)
    : _bucket(begin), _end_bucket(end), _ptr(NULL)
{
    if (_bucket)
    {
        _ptr = *_bucket;
    }
    
    if(!_ptr)
    {
        next_bucket();
    }
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_iterator& 
hash_table<K, V, F>::const_iterator::operator++()
{
    if(_ptr)
    {
        _ptr = _ptr->next();
    }

    if(!_ptr)
    {
        if(!next_bucket())
        {
            _bucket = NULL;
        }
    }
    return *this;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_iterator& 
hash_table<K, V, F>::const_iterator::operator++(int)
{
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_iterator::next_bucket()
{
    // Loop until a valid bucket is found or reached the end
    while (!_ptr && _bucket != NULL && ++_bucket != _end_bucket)
    {
        _ptr = *_bucket;
    }

    // A valid bucket was found and ptr is pointed to it
    if(_ptr)
    {
        return true;
    }

    return false;
}


template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::const_iterator::operator*() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type*
hash_table<K, V, F>::const_iterator::operator->() const
{
    throw_if_null();

    return &_ptr->value();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::key_type& 
hash_table<K, V, F>::const_iterator::key() const
{
    throw_if_null();

    return _ptr->key();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::const_iterator::value() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V, class F>
void hash_table<K, V, F>::const_iterator::throw_if_null() const
{
    if(!_ptr)
    {
        throw invalid_iterator("Cannot dereference iterator: points to NULL");
    }
    return;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_iterator::null() const
{
    return !_ptr;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_iterator::operator==(const self_type& rhs) const
{
    return _ptr == rhs._ptr && _bucket == rhs._bucket;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

/* forward_iterator */
template <class K, class V, class F>
typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::iterator::operator*()
{
    throw_if_null();

    return this->_ptr->value();
}

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type*
hash_table<K, V, F>::iterator::operator->()
{
    throw_if_null();

    return &this->_ptr->value();
}

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::iterator::value()
{
    throw_if_null();

    return this->_ptr->value();
}

template <class K, class V, class F>
void hash_table<K, V, F>::iterator::throw_if_null() const
{
    if(!this->_ptr)
    {
        throw invalid_iterator("Cannot dereference iterator: points to NULL");
    }
    return;
}

#endif // HASH_TABLE_CPP

