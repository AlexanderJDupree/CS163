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
void Sorted_List<T>::insert(iterator& position, const_reference data)
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

    // Edge case, if the tail is was the previous node, point tail to the new node
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
typename Sorted_List<T>::iterator Sorted_List<T>::end()
{
    return iterator(NULL);
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

    // Deletes the current node as the stack uniwnds
    delete current;

    return;
}
#endif //LINKED_LIST_CPP