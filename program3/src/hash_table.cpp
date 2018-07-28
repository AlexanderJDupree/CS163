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
    : _bucket_count(buckets), _buckets(new bucket[_bucket_count]) {}

template <class K, class V, class F>
bool hash_table<K, V, F>::empty()
{
    return true;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::size()
{
    return 0;
}

template <class K, class V, class F>
unsigned hash_table<K, V, F>::buckets()
{
    return _bucket_count;
}

#endif // HASH_TABLE_CPP

