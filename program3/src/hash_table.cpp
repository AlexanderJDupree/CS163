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
hash_table<K, V, F>::hash_table(const self_type& origin)
    : _size(0), _bucket_count(origin._bucket_count), _buckets(NULL),
      _hash(origin._hash), _default_object(origin._default_object)
{
    initialize_buckets();
    for (const_iterator it = origin.begin(); it != origin.end(); ++it)
    {
        insert(it.key(), it.value());
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
bool hash_table<K, V, F>::erase(const key_type& key)
{
    hash_node* target = _buckets[_hash(key) % _bucket_count];
    if (target)
    {
       return erase(target, key);
    }

    return false;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::erase(hash_node*& current, const key_type& key)
{
    if(!current)
    {
        return false;
    }

    if(current->key() == key)
    {
        hash_node* temp = current->next();

        unsigned index = _hash(key) % _bucket_count;
        if(current == _buckets[index])
        {
            _buckets[index] = NULL;
        }

        delete current;
        current = temp;
        return true;
    }

    return erase(current->next(), key);
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

    // Loop through the buckets, clearing each one
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

    // Recursively travel to the end of the chain
    clear_bucket(current->next());

    // Delete this node
    delete current;
    current = NULL;

    return;
}

template <class K, class V, class F>
hash_table<K, V, F>& hash_table<K, V, F>::default_object(const value_type& obj)
{
    _default_object = obj;
    return *this;
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type&
hash_table<K, V, F>::default_object() const
{
    return _default_object;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type&
hash_table<K, V, F>::default_object()
{
    return _default_object;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type&
hash_table<K, V, F>::find(const key_type& key)
{
    // Cast 'this' as const to use the logic in the const qualified find 
    // function. Then, return the value without the const qualifiers
    
    return const_cast<value_type&>(
            static_cast<const self_type&>(*this).find(key));
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type&
hash_table<K, V, F>::find(const key_type& key) const
{
    hash_node* target = _buckets[_hash(key) % _bucket_count];
    if (target)
    {
        // Loop until we find a node with a matching key
        while(target != NULL && target->key() != key)
        {
            target = target->next();
        }

        // A match was found
        if(target)
        {
            return target->value();
        }
    }

    // Search key failed
    return _default_object;
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
float hash_table<K, V, F>::load_factor() const
{
    return static_cast<float>(_size) / _bucket_count;
}

template <class K, class V, class F>
float hash_table<K, V, F>::spread() const
{
    return static_cast<float>(buckets_in_use()) / _bucket_count;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::buckets_in_use() const
{
    return count_if(_buckets, _buckets + _bucket_count, null_bucket());
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::largest_bucket() const
{
    unsigned largest = 0;
    for(bucket* i = _buckets; i != _buckets + _bucket_count; ++i)
    {
        const_bucket_iterator it(*i);
        unsigned count = count_if(it, const_bucket_iterator(), count_nodes());
        if (count > largest)
        {
            largest = count;
        }
    }
    return largest;
}

template <class K, class V, class F>
template <class InputIterator, class Predicate>
unsigned hash_table<K, V, F>::count_if(InputIterator begin, InputIterator end,
                                       Predicate pred) const
{
    unsigned sum = 0;
    for(; begin != end; ++begin)
    {
        if(pred(begin)) { ++sum; }
    }
    return sum;
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

template <class K, class V, class F>
typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::operator[](const key_type& key)
{
    return find(key);
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::operator[](const key_type& key) const
{
    return find(key);
}

template <class K, class V, class F>
bool hash_table<K, V, F>::operator==(const self_type& rhs) const
{
    const_iterator left = begin();
    const_iterator right = rhs.begin();

    while (left != end() && right != rhs.end())
    {
        if (left.key() != right.key() || left.value() != right.value())
        {
            return false;
        }
        ++left;
        ++right;
    }

    return left == end() && right == rhs.end();
}

template <class K, class V, class F>
bool hash_table<K, V, F>::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <class K, class V, class F>
hash_table<K, V, F>& hash_table<K, V, F>::operator=(const self_type& origin)
{
    // Utilize the copy constructor to copy origins data
    self_type copy(origin);

    // Swap ownership with the copy
    swap(*this, copy);

    // As the copy goes out of scope, it destructs with the old data
    return *this;
}

template <class K, class V, class F>
void hash_table<K, V, F>::swap(self_type& new_table, self_type& old_table)
{
    using std::swap;

    // Swap resources, reassign ownership
    swap(new_table._size, old_table._size);
    swap(new_table._hash, old_table._hash);
    swap(new_table._buckets, old_table._buckets);
    swap(new_table._bucket_count, old_table._bucket_count);
    swap(new_table._default_object, old_table._default_object);

    return;
}

/****** HASH NODE CLASS ******/

template <class K, class V, class F>
hash_table<K, V, F>::hash_node::hash_node(const K& key, const V& value, 
                                          hash_node* next)
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
/* const_bucket_iterator */
template <class K, class V, class F>
typename hash_table<K, V, F>::const_bucket_iterator& 
hash_table<K, V, F>::const_bucket_iterator::operator++()
{
    _ptr = _ptr->next();
    return *this;
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_bucket_iterator& 
hash_table<K, V, F>::const_bucket_iterator::operator++(int)
{
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::const_bucket_iterator::operator*() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type*
hash_table<K, V, F>::const_bucket_iterator::operator->() const
{
    throw_if_null();

    return &_ptr->value();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::key_type& 
hash_table<K, V, F>::const_bucket_iterator::key() const
{
    throw_if_null();

    return _ptr->key();
}

template <class K, class V, class F>
const typename hash_table<K, V, F>::value_type& 
hash_table<K, V, F>::const_bucket_iterator::value() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V, class F>
void hash_table<K, V, F>::const_bucket_iterator::throw_if_null() const
{
    if(!_ptr)
    {
        throw invalid_iterator("Cannot dereference iterator: points to NULL");
    }
    return;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_bucket_iterator::null() const
{
    return !_ptr;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_bucket_iterator::operator==(const self_type& rhs) const
{
    return _ptr == rhs._ptr;
}

template <class K, class V, class F>
bool hash_table<K, V, F>::const_bucket_iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

/* const_forward_iterator */
template <class K, class V, class F>
hash_table<K, V, F>::const_forward_iterator::const_forward_iterator(bucket* begin,
                                                                    bucket* end)
    : const_bucket_iterator(), _bucket(begin), _end_bucket(end)
{
    if (_bucket)
    {
        this->_ptr = *_bucket;
        if(!this->_ptr)
        {
            next_bucket();
        }
    }
}

template <class K, class V, class F>
typename hash_table<K, V, F>::const_iterator& 
hash_table<K, V, F>::const_iterator::operator++()
{
    if(this->_ptr)
    {
        this->_ptr = this->_ptr->next();
    }

    // If the next node is null move iterator to the next bucket
    if(!this->_ptr)
    {
        // If next bucket failed, the iterator has reached end of table
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
    while (!this->_ptr && _bucket != NULL && ++_bucket != _end_bucket)
    {
        this->_ptr = *_bucket;
    }

    // A valid bucket was found and ptr is pointed to it
    if(this->_ptr)
    {
        return true;
    }

    return false;
}

template <class K, class V, class F>
void hash_table<K, V, F>::const_iterator::throw_if_null() const
{
    if(!this->_ptr)
    {
        throw invalid_iterator("Cannot dereference iterator: points to NULL");
    }
    return;
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

