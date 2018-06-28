/*
File: linked_list.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef> // NULL
#include "iterator.h"

template <typename T>
class Sorted_List
{
  // Forward Declaration
  struct Node;

  public:

    /* Type definitions */
    typedef T                       value_type;
    typedef T*                      pointer;
    typedef T&                      reference;
    typedef const T&                const_reference;
    typedef const T*                const_pointer;
    typedef size_t                  size_type;
    typedef forward_iterator<Node>  iterator;


    ///@brief: Default constructor sets the head and tail pointers to NULL
    Sorted_List();

    /** 
      Copy Constructor
    */
    //List(const List<T>& list);

   
    ///@brief: Destructor calls the clear function to delete each node in the list
    ~Sorted_List();

    /* Modifiers */
    void push_front(const_reference data);

    /*
    @brief: inserts a new node AFTER the passed in position argument
    @param: postion is an iterator to the postion previous to the desired 
            insertion point
    @param: data is the value that will be copied onto the node
    @return: returns void, if the list is empty we call push_front
    */
    void insert(iterator& position, const_reference data);

    /*
    @brief: adds the data to a new node and places to the node into a sorted 
            position on the list.
    @param: data is a READ only reference to the original data and is copied to
            the data member of node.
    @return: true if the insertion was successful.
    */
    bool add(const_reference data);

    /*
    @brief: clear is a wrapper method for clear_list. It calls clear_list if
             the list is NOT empty.
    @return: void, does nothing if the list is empty. 
    */
    void clear();

    /* Capacity Functions */

    /*
    @brief: Tests if the container is empty.

    @return: True if the container is empty.
    */
    bool empty() const;

    /* Iterators */

    /* 
    @brief: creates an iterator that points to the first element of the list
    @return: returns a forward_iterator constructed off the head pointer
    */
    iterator begin();

    /*
    @brief: creates an iterator that points to one element past the end of the list
            dereferencing an end iterator causes undefined behavior
    @return: becuase tail always points to NULL, we return an iterator constructed
             from NULL. It is dangerous to dereference this iterator
    */
    iterator end();

  private:
    
    /* 
    @struct: Node

    @brief: Node is the atomic member for the linked list class. It stores
            the desired data and contains a pointer to the next node in the list.
    */
    struct Node
    {
        typedef T           value_type; 
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef Node        self_type;
        typedef Node*       pointer;
        typedef const Node* const_pointer;

        value_type data;
        Node* next;

        /*
        @brief: default constructor initializes the default constructor for
                value_type and points next to NULL
        */
        Node() : data(value_type()), next(NULL) {}

        /* 
        @brief: value constructor copies parameter into the data member and 
                points next to NULL
        @param: value is a READ only reference used to initialize the data member
        */
        Node(const_reference value) : data(value), next(NULL) {}
    };

    Node* head;
    Node* tail;

    /* Private Functions */

    /*
    @brief: recursively calls itself until the end of the list is reached, while
           call stack unwinds clear_list deletes the node associated with 
           current.

    @param: current is a pointer to the current node in the list
    @return: true, does nothing if the list is empty.
    */
    void clear_list(Node* current);
};

/*
Because this is a templated class, we need to include the implementation in 
the header file so the compiler can instantiate the methods with the right type 
*/
#include "linked_list.cpp"

#endif //LINKED_LIST_H