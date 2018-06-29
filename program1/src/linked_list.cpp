/*
File: linked_list.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "linked_list.h"

template <typename T>
Sorted_List<T>::Sorted_List() : head(NULL), tail(NULL) {}

template <typename T>
Sorted_List<T>::~Sorted_List()
{
    clear();
}

/* Modifiers */

template <typename T>
bool Sorted_List<T>::add(const_reference data)
{
    if (empty())
    {
        push_front(data);
        return true;
    }

    // Find the index to insert into
    const_iterator position = begin();

    if(find_position(data, begin(), position))
    {
        insert(position, data);
        return true;
    }

    return false;
    
}

template <typename T>
void Sorted_List<T>::push_front(const_reference data)
{
    Node* temp = new Node(data);

    temp->next = head;
    head = temp;

    if (tail == NULL)
    {
        tail = head;
    }

    return;
}

template <typename T>
void Sorted_List<T>::insert(const_iterator& position, const_reference data)
{
    if(empty())
    {
        // List is empty, so we can have the push_front method do all the work
        push_front(data);

        // Update the iterators position to point to a valid element
        position = iterator(head);
        return;
    }

    Node* new_node = new Node(data);
    
    // Point the new node to what the previous node was pointing to
    new_node->next = position.node->next;

    // Point the previous node to the new node
    position.node->next = new_node;

    // Edge case, if the tail is was the previous node, point tail to new node
    if (tail->next == new_node)
    {
        tail = new_node;
    }

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

/* ITERATORS */
template <typename T>
typename Sorted_List<T>::iterator Sorted_List<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename Sorted_List<T>::const_iterator Sorted_List<T>::begin() const
{
    return const_iterator(head);
}

template <typename T>
typename Sorted_List<T>::iterator Sorted_List<T>::end()
{
    return iterator(NULL);
}

template <typename T>
typename Sorted_List<T>::const_iterator Sorted_List<T>::end() const
{
    return const_iterator(NULL);
}

/* Private Functions */
template <typename T>
void Sorted_List<T>::clear_list(Node* current)
{
    // While the current node pointer is not at the end of the list
    if (current != tail)
    {
        // Recursive call to travel to the end of the list
        clear_list(current->next);
    }

    // Deletes the current node as the stack unwinds
    delete current;

    return;
}

template <typename T>
bool Sorted_List<T>::find_position(const_reference data, const_iterator& pos, 
                                                         const_iterator& prev)
{
    if (data == *pos)
    {
        return false;
    }
    if (data < *pos)
    {
        return true;
    }

    prev = pos;

    return find_position(data, ++pos, prev);
}

/*******************************************************************************
ITERATOR CLASS
*******************************************************************************/

template <typename T>
Sorted_List<T>::iterator::forward_iterator() : node(NULL) {}

template <typename T>
Sorted_List<T>::iterator::forward_iterator(pointer ptr) : node(ptr) {}

/* Operator Overloads */
template <typename T>
typename Sorted_List<T>::iterator& 
Sorted_List<T>::forward_iterator::operator++()
{
    // reassign node member to point to the next element in the container
    node = node->next;
    return *this;
}

template <typename T>
typename Sorted_List<T>::iterator& 
Sorted_List<T>::iterator::operator++(int)
{
    // Create a copy to satisfy postfix incrementation requirements
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <typename T>
typename Sorted_List<T>::iterator::reference
Sorted_List<T>::iterator::operator*()
{
    return node->data;
}

template <typename T>
bool Sorted_List<T>::iterator::operator==(const self_type& rhs) const
{
    // Compare memory addresses, NOT the value of the data member
    return node == rhs.node;
}

template <typename T>
bool Sorted_List<T>::iterator::operator!=(const self_type& rhs) const
{
    // return the logical NOT of the equality comparison
    return !(*this == rhs);
}

/* CONST_ITERATOR */

template <typename T>
typename Sorted_List<T>::const_iterator::const_reference 
Sorted_List<T>::const_iterator::operator*() const
{
    return this->node->data;
}


#endif //LINKED_LIST_CPP
