/*
File: linked_list.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef> // NULL

template <typename T>
class Sorted_List
{
  public:

    // forward declaration
    class const_forward_iterator;

    /* Type definitions */
    typedef T                      value_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    typedef const T&               const_reference;
    typedef const T*               const_pointer;
    typedef size_t                 size_type;
    typedef const_forward_iterator const_iterator;
    typedef Sorted_List<T>         self_type;

    // Instantiates an EMPTY list
    Sorted_List();

    // Copies each element in the original list onto this list
    Sorted_List(const Sorted_List<T>& origin);
   
    // Uses clear() to delete each element in the list
    ~Sorted_List();
    
    // Inserts UNIQUE data into a position in the list that will keep the list 
    // in a SORTED state
    bool add(const_reference data);

    // wrapper method for clear_list, if the list is empty does nothing
    void clear();

    // returns true if the list is empty
    bool empty() const;

    // returns the number of elements in the list
    size_type size() const;

    /* Iterators */
    // returns a read only iterator to the first element in the list
    const_iterator begin() const;

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
        Node() : data(value_type()), next(NULL) {}

        // Value constructor points next to NULL and initializes data to the 
        // parameter
        Node(const_reference value) : data(value), next(NULL) {}

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


    // Recursively travel the list until data compares '<' than the next element
    // Inserts into that position
    bool insert(Node* current, const_reference data);

     
    // Adds an element to the front of the list
    void push_front(const_reference data);

    // Adds an element to the back of the list
    void push_back(const_reference data);


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
        typedef typename Node::value_type      value_type;
        typedef typename Node::const_reference const_reference;
        typedef Node*                          pointer;
        typedef const_forward_iterator         self_type;

        /* Constructors */

        // default constructor points the iterator to NULL
        const_forward_iterator() : node(NULL) {}

        // Value constructor initializers the pointer to point to the passed in
        // parameter
        const_forward_iterator(pointer ptr) : node(ptr) {}

        /* Operator Overloads */

        // prefix increment points the iterator to the next element in the list
        self_type& operator++(); // Prefix ++

        // postfix increment makes a COPY of the iterator, calls the prefix 
        // increment, and returns the COPY
        self_type& operator++(int); // Postfix ++

        // dereference operator allows a READ only inspection of the data member
        const_reference operator*() const;

        // returns true if each iterator is pointing to the same address in
        // memory
        bool operator==(const self_type& rhs) const;

        // returns the logical not of the equality operator
        bool operator!=(const self_type& rhs) const;
      
      private:

        pointer node;
    };
};

/*
Because this is a templated class, we need to include the implementation in 
the header file so the compiler can instantiate the methods with the right type 
*/
#include "linked_list.cpp"

#endif //LINKED_LIST_H
