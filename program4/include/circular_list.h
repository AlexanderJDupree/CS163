/*
File: circular_list.h

Brief: circular_linked_list is a data structure that stores data onto a node as 
       well as the address for the next element in the container. This last node
       of the list will point to the first, this gives the container a cyclic
       or circular trait. 

Author: Alexander DuPree

Class: CS163

Assignment: program 2

Date: 07/24/2018
*/

#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <cstddef> // NULL
#include <algorithm> // std::swap
#include <stdexcept> // std::logic_error

template <typename T>
class circular_linked_list
{
  public:

    // forward declaration
    class const_forward_iterator;
    class forward_iterator;

    /* Type definitions */
    typedef T                      value_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    typedef const T&               const_reference;
    typedef const T*               const_pointer;
    typedef size_t                 size_type;
    typedef forward_iterator       iterator;
    typedef const_forward_iterator const_iterator;
    typedef circular_linked_list<T>  self_type;

    /****** CONSTRUCTORS ******/

    // Instantiates an EMPTY list
    circular_linked_list();

    // Ranged based constructor 
    template <class InputIterator>
    circular_linked_list(InputIterator begin, InputIterator end);

    // Copy Constructor
    circular_linked_list(const self_type& origin);
   
    // Uses clear() to delete each element in the list
    ~circular_linked_list();
     
    /****** MODIFIERS ******/

    // Adds an element to the back of the list
    self_type& push_back(const_reference data);

    // Removes the element at the front of the list
    self_type& pop_front();

    // Pops the front element into the out_parameter
    reference pop_front(reference out_param);

    // wrapper method for clear_list, if the list is empty does nothing
    self_type& clear();

    // Removes the first item fullfilling the predicate functor
    template <class Predicate>
    bool remove_if(Predicate pred);

    /****** CAPACITY ******/

    // returns true if the list is empty
    bool empty() const;

    // returns the number of elements in the list
    size_type size() const;

    /****** ITERATORS ******/

    // returns a read/write iterator to the first element in the list
    iterator begin();

    // returns a read only iterator to the first element in the list
    const_iterator begin() const;

    // end iterators are equivalent to begin iterators
    iterator end();
    const_iterator end() const;

    /****** ELEMENT ACCESS ******/

    // Allows read only inspection of the front in the list
    // throws if list is empty
    const_reference front() const;

    // Alows read only inspection of the rear of the list
    // throws if list is empty
    const_reference back() const;

    /****** COMPARISON OPERATORS ******/

    // Compares sizes, then compares each element of the list for equality
    bool operator==(const self_type& rhs) const;

    // returns the logical NOT of the equality comparison
    bool operator!=(const self_type& rhs) const;

    /****** COPY-ASSIGNMENT AND SWAP ******/

    // creates a copy of the origin, then swaps ownership with the copy
    self_type& operator=(const self_type& origin);

    // Swaps pointers to each other's resources. effectively reassigning 
    // ownership.
    static void swap(self_type& new_list, self_type& old_list);

  private:
    
    /* 
    @struct: Node

    @brief: Node is the atomic member for the linked list. It stores the desired 
            data and contains a pointer to the next node in the list.
    */
    struct Node
    {
        // Default values are default constrution and NULL
        Node(const_reference value = value_type(), Node* next = NULL) 
            : data(value), next(next) {}

        value_type data;
        Node* next;
    };

    Node* _rear; 
    Node* _front;

    size_type _size; // Keeps track of the number of elements in the list

    /****** RECURSIVE FUNCTIONS ******/

    // Recursive function that calls itself until it reaches the end of the list
    // then while the stack unwinds it deletes each node
    void clear_list(Node*& current);

    // Recursively travels the list removing the first element fullfiling the
    // Predicate functor
    template <class Predicate>
    int remove_if(Predicate pred, Node* current);

    /****** SUBROUTINES ******/

    // Throws a logic error exception if the Node* is NULL
    void throw_if_null(Node* node) const;

    public:

    /*
    @class: const_forward_iterator
    
    @brief: The const_forward_iterator is a read-only abstraction of the node 
            pointer. The const_forward_iterator provides methods for inspecting
            data, and incrementation. This iterator type does not support 
            decrementation or random access

            Because the iterator does not manage any resources and it's only 
            member is a pointer, we allow the use of the DEFAULT destructor, 
            copy constructor, and copy-assignment operator.
    */
    class const_forward_iterator
    {
      public:

        typedef const_forward_iterator  self_type;

        /* Constructors */

        // Defaults to NULL iterator 
        const_forward_iterator(Node* ptr = NULL) : node(ptr) {}

        /* Operator Overloads */

        // prefix increment points the iterator to the next element in the list
        self_type& operator++(); // Prefix ++

        // postfix increment makes a COPY of the iterator, calls the prefix 
        // increment, and returns the COPY
        self_type& operator++(int); // Postfix ++

        // dereference operator allows a READ only inspection of the data member
        const_reference operator*() const;

        // arrow operator allows returns a READ only reference to the data member
        const_pointer operator->() const;

        // Returns true if the iterator is NULL
        bool null() const;

        // returns true if each iterator is pointing to the same address in
        // memory
        bool operator==(const self_type& rhs) const;

        // returns the logical not of the equality operator
        bool operator!=(const self_type& rhs) const;

      protected:

        Node* node;
    };

    /*
    @class: forward_iterator
    
    @brief: The forward_iterator is a read/write abstraction of the node 
            pointer. The forward_iterator inherits all methods from the 
            const_forward_iterator but overrides the reference operators
            to allow the client to mutate data
    */
    class forward_iterator : public const_forward_iterator
    {
      public:

        /* Type definitions */
        typedef forward_iterator    self_type;

        forward_iterator(Node* ptr = NULL) : const_forward_iterator(ptr) {}

        // Dereference operator allows a read/write access to data member
        reference operator*();

        // Arrow operator allows a read/write reference to data member
        pointer operator->();
    };
};

/*
Because this is a templated class, we need to include the implementation in 
the header file so the compiler can instantiate the methods with the right type 
*/
#include "circular_list.cpp"

#endif //CIRCULAR_LIST_H
