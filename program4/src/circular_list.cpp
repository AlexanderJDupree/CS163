/*
File: circular_list.cpp

Description: Implementation for templated circular_linked_list class. Defines
             methods for modifiers, capacity checks, and iteration of the 
             circular_linked_list data structure.

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/11/2018
*/

#ifndef CIRCULAR_LIST_CPP
#define CIRCULAR_LIST_CPP

#include "circular_list.h"

/****** CONSTRUCTORS ******/

// default constructor
template <typename T>
circular_linked_list<T>::circular_linked_list() 
    : _rear(NULL), _front(NULL), _size(0) {}

// ranged based constructor
template <typename T>
template <class InputIterator>
circular_linked_list<T>::circular_linked_list(InputIterator begin, InputIterator end) 
    : _rear(NULL), _front(NULL), _size(0)
{
    for(; begin != end; ++begin)
    {
        push_back(*begin);
    }
}

// Copy constructor
template <typename T>
circular_linked_list<T>::circular_linked_list(const self_type& origin) 
    : _rear(NULL), _front(NULL), _size(0)
{
    Node* temp = origin._front;
    do {
        push_back(temp->data);
        temp = temp->next;
    } while (temp != origin._front);
}

// Destructor
template <typename T>
circular_linked_list<T>::~circular_linked_list()
{
    clear();
}

/****** MODIFIERS ******/

template <typename T>
circular_linked_list<T>& circular_linked_list<T>::push_back(const_reference data)
{
    if(!_rear) // List is empty
    {
        _rear = new Node(data);
        _front = _rear;
        _rear->next = _front;
    }
    else
    {
        Node* temp = new Node(data, _front);

        _rear->next = temp;
        _rear = temp;
    }

    ++_size;
    return *this;
}

template <typename T>
circular_linked_list<T>& circular_linked_list<T>::pop_front()
{
    if (!_rear) // List is empty
    {
        return *this;
    }

    if(_front == _rear) // Only one item in the list
    {
        delete _front;
        _front = NULL;
        _rear = NULL;
    }
    else
    {
        Node* temp = _front->next;
        delete _front;

        _front = temp;
        _rear->next = temp;
    }

    --_size;
    return *this;
}

template <typename T>
T& circular_linked_list<T>::pop_front(reference out_param)
{
    if (!_rear) // List is empty
    {
        return out_param;
    }

    out_param = _front->data;

    pop_front();
    return out_param;
}

template <typename T>
circular_linked_list<T>& circular_linked_list<T>::clear()
{
    if(!_rear)
    {
        return *this;
    }

    // break apart the list
    _rear->next = NULL;

    // recursively clear the list
    clear_list(_front);

    _size = 0;
    _rear = NULL;
    return *this;
}

template <typename T>
void circular_linked_list<T>::clear_list(Node*& current)
{
    // While the current node pointer is not at the end of the list
    if (current == NULL)
    {
        return;
    }

    Node* next = current->next;

    delete current;
    current = NULL;

    return clear_list(next);
}

template <typename T>
template <class Predicate>
bool circular_linked_list<T>::remove_if(Predicate pred)
{
    if (!_rear)
    {
        return false;
    }

    // If there is one element in the list and it is the target
    if(pred(_front->data) && _front == _rear)
    {
        pop_front();
        return true;
    }

    return remove_if(pred, _front);
}

template <typename T>
template <class Predicate>
int circular_linked_list<T>::remove_if(Predicate pred, Node* current)
{
    // Base case: no element in the list fulfills the predicate
    if(current == _rear)
    {
        return pred(_rear->data);
    }

    if(pred(current->data)) // Target found
    {
        return 1;
    }

    int recursive_signal = remove_if(pred, current->next);
    if(recursive_signal == 1)
    {
        Node* target = current->next;
        current->next = target->next;
        delete target;
        --_size;
        return 2;
    }

    return recursive_signal;
}

/****** CAPACITY ******/

template <typename T>
bool circular_linked_list<T>::empty() const
{
    return !(_rear);
}
template <typename T>
typename circular_linked_list<T>::size_type circular_linked_list<T>::size() const
{
    return _size;
}

/****** ITERATORS ******/

template <typename T>
typename circular_linked_list<T>::iterator
circular_linked_list<T>::begin()
{
    return iterator(_front);
}

template <typename T>
typename circular_linked_list<T>::const_iterator 
circular_linked_list<T>::begin() const
{
    return const_iterator(_front);
}

template <typename T>
typename circular_linked_list<T>::iterator
circular_linked_list<T>::end()
{
    return iterator(_front);
}

template <typename T>
typename circular_linked_list<T>::const_iterator 
circular_linked_list<T>::end() const
{
    return const_iterator(_front);
}

/****** ELEMENT ACCESS ******/

template <typename T>
const T& circular_linked_list<T>::front() const
{
    throw_if_null(_front);

    return _front->data;
}

template <typename T>
const T& circular_linked_list<T>::back() const
{
    throw_if_null(_rear);

    return _rear->data;
}

template <typename T>
void circular_linked_list<T>::throw_if_null(Node* node) const
{
    if (node)
    {
        return;
    }

    throw std::logic_error("Element access fail, NULL pointer");
}

/****** COMPARISON OPERATORS ******/

template <typename T>
bool circular_linked_list<T>::operator==(const self_type& rhs) const
{
    // Compare sizes first
    if (rhs._size != _size)
    {
        return false;
    }

    Node* left = _front;
    Node* right = rhs._front;

    do {
        // If any element does not match then return false
        if (left->data != right->data)
        {
            return false;
        }

        left = left->next;
        right = right->next;

    } while(left != _front);

    // each element matched and the sizes were the same
    return true;
}

template <typename T>
bool circular_linked_list<T>::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

/****** COPY-ASSIGNMENT AND SWAP ******/

template <typename T>
typename circular_linked_list<T>::self_type& 
circular_linked_list<T>::operator=(const self_type& origin)
{
    // Create a copy of the list, if an exception is thrown then the state of 
    // original list and our list is unchanged
    circular_linked_list<T> copy(origin);

    // Swap ownership of resources with the copy
    swap(*this, copy);

    // As the copy goes out of scope it destructs with the old data
    return *this;
}

template <typename T>
void circular_linked_list<T>::swap(self_type& new_list, self_type& old_list)
{
    using std::swap;

    // Swaps pointers, reassigns ownership
    swap(new_list._rear, old_list._rear);
    swap(new_list._front, old_list._front);
    swap(new_list._size, old_list._size);
    return;
}

/*******************************************************************************
ITERATOR CLASS
*******************************************************************************/

/* Operator Overloads */
template <typename T>
typename circular_linked_list<T>::const_iterator& 
circular_linked_list<T>::const_iterator::operator++()
{
    // reassign node member to point to the next element in the container
    node = node->next;
    return *this;
}

template <typename T>
typename circular_linked_list<T>::const_iterator& 
circular_linked_list<T>::const_iterator::operator++(int)
{
    // Create a copy to satisfy postfix incrementation requirements
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
bool circular_linked_list<T>::const_iterator::null() const
{
    return node == NULL;
}

template <typename T>
bool circular_linked_list<T>::const_iterator::operator==(const self_type& rhs) const
{
    // Compare memory addresses, NOT the value of the data member
    return node == rhs.node;
}

template <typename T>
bool circular_linked_list<T>::const_iterator::operator!=(const self_type& rhs) const
{
    // return the logical NOT of the equality comparison
    return !(*this == rhs);
}

template <typename T>
typename circular_linked_list<T>::const_reference 
circular_linked_list<T>::const_iterator::operator*() const
{
    return node->data;
}

template <typename T>
typename circular_linked_list<T>::const_pointer
circular_linked_list<T>::const_iterator::operator->() const
{
    return &node->data;
}

template <typename T>
typename circular_linked_list<T>::reference
circular_linked_list<T>::iterator::operator*() 
{
    return this->node->data;
}

template <typename T>
typename circular_linked_list<T>::pointer
circular_linked_list<T>::iterator::operator->()
{
    return &this->node->data;
}

#endif // CIRCULAR_LIST_CPP
