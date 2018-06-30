/*
File: linked_list.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include <iostream>
#include "linked_list.h"

template <typename T>
Sorted_List<T>::Sorted_List() : head(NULL), tail(NULL), _size(0) {}

template <typename T>
Sorted_List<T>::Sorted_List(const Sorted_List<T>& origin) 
    : head(NULL), tail(NULL), _size(0)
{
    Sorted_List<T>::const_iterator it;
    for (it = origin.begin(); it != origin.end(); ++it)
    {
        push_back(*it);
    }
}

template <typename T>
Sorted_List<T>::~Sorted_List()
{
    clear();
}

/* Modifiers */

template <typename T>
bool Sorted_List<T>::add(const_reference data)
{
    if(empty() || data < head->data)
    {
        push_front(data);
        return true;
    }

    return insert(head, data);
}

template <typename T>
bool Sorted_List<T>::insert(Node* current, const_reference data)
{
    // return is we've looked at every node or data is duplicated
    if (current->data == data)
    {
        return false;
    }

    if (current == tail)
    {
        push_back(data);
        return true;
    }

    // Insert here if data is less than the next node and it is not duplicated
    if(data < current->next->data && data != current->next->data)
    {
        Node* temp = new Node(data);

        temp->next = current->next;

        current->next = temp;
        
        ++_size;
        return true;
    }

    // Recursively travel the list
    return insert(current->next, data);
}

template <typename T>
void Sorted_List<T>::push_front(const_reference data)
{
    Node* temp = new Node(data);

    // connect temp to the front of the list
    temp->next = head;
    head = temp;

    if (tail == NULL)
    {
        tail = head;
    }

    ++_size;
    return;
}

template <typename T>
void Sorted_List<T>::push_back(const_reference data)
{
    if(empty())
    {
        push_front(data);
        return;
    }

    Node* temp = new Node(data);

    tail->next = temp;
    tail = temp;

    ++_size;
    return;
}

template <typename T>
void Sorted_List<T>::clear()
{
    if(empty())
    {
        return;
    }

    // clear_list is a recursive function that deletes each node of the list
    clear_list(head);
    return;
}

template <typename T>
void Sorted_List<T>::clear_list(Node*& current)
{
    // While the current node pointer is not at the end of the list
    if (current != tail)
    {
        // Recursive call to travel to the end of the list
        clear_list(current->next);
    }

    // Deletes the current node as the stack unwinds
    delete current;
    current = NULL;

    return;
}

/* Capacity Functions */
template <typename T>
bool Sorted_List<T>::empty() const
{
    /*
    Because head is only NULL, or 0, when the list is empty we can return the 
    logical NOT of head. This returns true iff head is NULL.
    */

    return !(head);
}

template <typename T>
typename Sorted_List<T>::size_type Sorted_List<T>::size() const
{
    return _size;
}

/* ITERATORS */
template <typename T>
typename Sorted_List<T>::const_iterator Sorted_List<T>::begin() const
{
    return const_iterator(head);
}

template <typename T>
typename Sorted_List<T>::const_iterator Sorted_List<T>::end() const
{
    return const_iterator(NULL);
}

/* Operator Overloads */
template <typename T>
bool Sorted_List<T>::operator==(const self_type& rhs)
{
    if (rhs.size() != size())
    {
        return false;
    }

    Sorted_List<T>::const_iterator left = begin();
    Sorted_List<T>::const_iterator right = rhs.begin();

    while(left != end())
    {
        if (*left != *right)
        {
            return false;
        }
        ++left;
        ++right;
    }

    return true;
}

template <typename T>
bool Sorted_List<T>::operator!=(const self_type& rhs)
{
    return !(*this == rhs);
}

template <typename T>
typename Sorted_List<T>::self_type& Sorted_List<T>::operator=(const self_type& origin)
{
    // Create a copy of the list, if an exception is thrown then the state of 
    // original list and our list is unchanged
    Sorted_List<T> copy(origin);

    // Swap ownership of resources with the copy
    swap(*this, copy);

    // As the copy goes out of scope is destructs with the old data with it
    return *this;
}

template <typename T>
void Sorted_List<T>::swap(self_type& new_list, self_type& old_list)
{
    using std::swap;

    // Swaps pointers, reassigns ownership
    swap(new_list.head, old_list.head);
    swap(new_list.tail, old_list.tail);
    swap(new_list._size, old_list._size);
    return;
}
/*******************************************************************************
ITERATOR CLASS
*******************************************************************************/

/* Operator Overloads */
template <typename T>
typename Sorted_List<T>::const_iterator& 
Sorted_List<T>::const_iterator::operator++()
{
    // reassign node member to point to the next element in the container
    node = node->next;
    return *this;
}

template <typename T>
typename Sorted_List<T>::const_iterator& 
Sorted_List<T>::const_iterator::operator++(int)
{
    // Create a copy to satisfy postfix incrementation requirements
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
bool Sorted_List<T>::const_iterator::operator==(const self_type& rhs) const
{
    // Compare memory addresses, NOT the value of the data member
    return node == rhs.node;
}

template <typename T>
bool Sorted_List<T>::const_iterator::operator!=(const self_type& rhs) const
{
    // return the logical NOT of the equality comparison
    return !(*this == rhs);
}

template <typename T>
typename Sorted_List<T>::const_iterator::const_reference 
Sorted_List<T>::const_iterator::operator*() const
{
    return node->data;
}

#endif //LINKED_LIST_CPP
