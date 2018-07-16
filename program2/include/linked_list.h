/*
File: linked_list.h

Description: linear_linked_list is a data structure that stores data onto a node
             as well as the address for the next element in the container.

             This implementation for the linear linked list is a fully templated
             class. This allows the linear_linked_list to be instantiated to 
             store any data types. 

             By default the linear linked list COPIES the data onto the node. 
             This requires that the data object have a copy constructor defined
             or can be shallow copied with the default constructor.

             This linear linked list implemented with a add_unique method that
             will add UNIQUE elements into the container in a sorted state. 
             This operation requires the use of the '<' and the '==' operator to
             be defined as well. 

             To access data or traverse the list, this linear linked list makes 
             use of forward iterators. The forward iterator cannot be decremented.
             The end iterator represents the element one-past the end of the
             list which is a null pointer. dereferencing end iterators causes 
             undifined behavior.

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 06/27/2018
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef> // NULL
#include <algorithm> // std::swap

template <typename T>
class linear_linked_list
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
    typedef linear_linked_list<T>  self_type;

    // Instantiates an EMPTY list
    linear_linked_list();

    // Ranged based constructor
    template <class InputIterator>
    linear_linked_list(InputIterator begin, InputIterator end);

    // Copies each element in the original list onto this list
    linear_linked_list(const self_type& origin);
   
    // Uses clear() to delete each element in the list
    ~linear_linked_list();
     
    // Adds an element to the front of the list
    self_type& push_front(const_reference data);

    // Adds an element to the back of the list
    self_type& push_back(const_reference data);

    // Removes the element at the front of the list
    self_type& pop_front();

    reference pop_front(reference out_param);

    // wrapper method for clear_list, if the list is empty does nothing
    void clear();

    // returns true if the list is empty
    bool empty() const;

    // Removes the first item fullfilling the predicate functor
    template <class Predicate>
    bool remove_if(Predicate pred);

    // returns the number of elements in the list
    size_type size() const;

    /* Iterators */

    // returns a read/write iterator to the first element in the list
    iterator begin();

    // returns a read only iterator to the first element in the list
    const_iterator begin() const;

    iterator end();
    // returns an iterator to one-past the last element in the list. 
    // dereferencing end() iterators causes undefined behavior
    const_iterator end() const;

    /* Operator Overloads */
    // Compares sizes, then comapres each element of the list for equality
    bool operator==(const self_type& rhs) const;

    // returns the logical NOT of the equality comparison
    bool operator!=(const self_type& rhs) const;

    // creates a copy of the origin, then swaps ownership with the copy
    self_type& operator=(const self_type& origin);

    // Swaps pointers to each other's resources. effectively reassigning 
    // ownership.
    static void swap(self_type& new_list, self_type& old_list);

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
        typedef T*          pointer;
        typedef const T*    const_pointer;

        
        // Default contructor points next to NULL and initializes data to it's 
        // default construction
        Node(const_reference value = value_type(), Node* next = NULL) 
            : data(value), next(next) {}

        value_type data;
        Node* next;

    };

    Node* head;
    Node* tail;

    size_type _size; // Keeps track of the number of elements in the list

    /* Private Functions */

    // Recursive function that calls itself until it reaches the end of the list
    // then while the stack unwinds it deletes each node
    void clear_list(Node*& current);

    // Recursively travels the list removing the first element fullfiling the
    // Predicate functor
    template <class Predicate>
    bool remove_if(Predicate pred, Node* current);

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

        /* Type definitions */
        typedef T                       value_type;
        typedef const T&                const_reference;
        typedef const T*                const_pointer;
        typedef const_forward_iterator  self_type;

        /* Constructors */

        // default constructor points the iterator to NULL
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
        typedef T                   value_type;
        typedef T&                  reference;
        typedef T*                  pointer;
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
#include "linked_list.cpp"

#endif //LINKED_LIST_H
