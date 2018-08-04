/*
File: binary_search_tree.cpp

Brief: 

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/24/2018
*/

#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP

#include "binary_search_tree.h"

template <class T>
binary_tree<T>::binary_tree()
    : _size(0), _root(NULL) {}

template <class T>
template <class InputIterator>
binary_tree<T>::binary_tree(InputIterator begin, InputIterator end)
    : _size(0), _root(NULL)
{
    for(; begin != end; ++begin)
    {
        insert(*begin);
    }
}

template <class T>
binary_tree<T>::~binary_tree()
{
    clear();
}

template <class T>
binary_tree<T>& binary_tree<T>::insert(const value_type& data)
{
    insert(data, _root);
    ++_size;
    return *this;
}

template <class T>
void binary_tree<T>::insert(const value_type& data, b_node*& root)
{
    if(!root)
    {
        root = new b_node(data);
        return;
    }

    if(data < root->data())
    {
        return insert(data, root->left());
    }
    
    return insert(data, root->right());
}

template <class T>
binary_tree<T>& binary_tree<T>::clear()
{
    delete_leaf functor;
    postorder_traversal(_root, functor);

    _size = 0;
    return *this;
}

template <class T>
bool binary_tree<T>::empty() const
{
    return !(_root);
}

template <class T>
unsigned binary_tree<T>::size() const
{
    return _size;
}

template <class T>
unsigned binary_tree<T>::height() const
{
    return height(_root);
}

template <class T>
const T& binary_tree<T>::root() const
{
    throw_if_null(_root, "Error in root(), root is null");

    return _root->data();
}

template <class T>
const T& binary_tree<T>::default_object() const
{
    return _default_object;
}

template <class T>
binary_tree<T>& binary_tree<T>::default_object(const_reference obj)
{
    _default_object = obj;
    return *this;
}

template <class T>
const T& binary_tree<T>::find(const_reference key) const
{
    return find(key, _root);
}

template <class T>
const T& binary_tree<T>::find(const_reference key, b_node* root) const
{
    if(!root) // No match was found
    {
        return _default_object;
    }

    if(key == root->data()) // Match was found
    {
        return root->data();
    }

    if(key < root->data())
    {
        return find(key, root->left());
    }

    return find(key, root->right());
}

template <class T>
typename binary_tree<T>::const_iterator
binary_tree<T>::begin()
{
    build_traversal_queue functor(&_traversal_queue);
    inorder_traversal(_root, functor);

    return const_iterator(&_traversal_queue);
}

template <class T>
typename binary_tree<T>::const_iterator
binary_tree<T>::end()
{
    return const_iterator(NULL);
}

template <class T>
template <class Functor>
void binary_tree<T>::inorder_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    inorder_traversal(root->left(), func);

    func(root);

    inorder_traversal(root->right(), func);

    return;
}

template <class T>
template <class Functor>
void binary_tree<T>::postorder_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    postorder_traversal(root->left(), func);

    postorder_traversal(root->right(), func);

    func(root);

    return;
}

template <class T>
unsigned binary_tree<T>::height(b_node* root) const
{
    if(!root)
    {
        return 0;
    }

    return 1 + std::max(height(root->left()), height(root->right()));
}

template <class T>
void binary_tree<T>::throw_if_null(b_node* node, const char* msg) const
{
    if(!node)
    {
        throw std::logic_error(msg);
    }
    return;
}

/****** B_NODE CLASS ******/ 

template <class T>
binary_tree<T>::b_node::b_node(const T& data, b_node* left, b_node* right)
    : _data(data), _left(left), _right(right) {}

template <class T>
const T& binary_tree<T>::b_node::data() const
{
    return _data;
}

template <class T>
typename binary_tree<T>::b_node*& binary_tree<T>::b_node::left()
{
    return _left;
}

template <class T>
typename binary_tree<T>::b_node*& binary_tree<T>::b_node::right()
{
    return _right;
}

/****** FORWARD ITERATOR ******/

template <class T>
binary_tree<T>::const_iterator::const_forward_iterator(queue* traversal_state)
    : _traversal_queue(traversal_state), _ptr(NULL)
{
    if(_traversal_queue)
    {
        _traversal_queue->pop_front(_ptr);
    }
}

template <class T>
typename binary_tree<T>::const_iterator& 
binary_tree<T>::const_iterator::operator++()
{
    if(!_traversal_queue || _traversal_queue->empty())
    {
        _ptr = NULL;
    }
    else
    {
        _traversal_queue->pop_front(_ptr);
    }

    return *this;
}

template <class T>
typename binary_tree<T>::const_iterator& 
binary_tree<T>::const_iterator::operator++(int)
{
    const_iterator copy(*this);

    ++(*this);

    return copy;
}

template <class T>
const T& binary_tree<T>::const_iterator::operator*() const
{
    throw_if_null();

    return _ptr->data();
}

template <class T>
const T* binary_tree<T>::const_iterator::operator->() const
{
    throw_if_null();

    return &_ptr->data();
}

template <class T>
bool binary_tree<T>::const_iterator::null() const
{
    return !(_ptr);
}

template <class T>
bool binary_tree<T>::const_iterator::operator==(const self_type& rhs) const
{
    return _ptr == rhs._ptr;
}

template <class T>
bool binary_tree<T>::const_iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <class T>
void binary_tree<T>::const_iterator::throw_if_null() const
{
    if(!_ptr)
    {
        throw invalid_iterator();
    }

    return;
}

#endif // BINARY_TREE_CPP

