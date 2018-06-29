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
  // Forward Declaration
  struct Node;

  public:

  class forward_iterator;
  class const_forward_iterator;

    /* Type definitions */
    typedef T                      value_type;
    typedef T*                     pointer;
    typedef T&                     reference;
    typedef const T&               const_reference;
    typedef const T*               const_pointer;
    typedef size_t                 size_type;
    typedef forward_iterator       iterator;
    typedef const_forward_iterator const_iterator;


    /**
    @brief: Default constructor is called whenever this object is instantiated
    The container will be EMPTY by default
    */
    Sorted_List();

    /** 
      Copy Constructor
    */
    //List(const List<T>& list);

   
    /**
    @brief: Destructor is called explicitly with delete or when the object
    goes out of scope. Frees up all memory associated with the list
    */
    ~Sorted_List();

    /* Modifiers */

    /**
    @brief: adds an element to the front of the list
    @param: data is the value that will be copied onto the list
    */
    void push_front(const_reference data);

    /*
    @brief: inserts a new element into the list AFTER the specified position
    @param: postion is an iterator to the postion PREVIOUS to the desired 
            insertion point
    @param: data is the value that will be copied onto the list
    @return: returns void, if the list is empty we call push_front
    */
    void insert(const_iterator& position, const_reference data);

    /*
    @brief: inserts the data into a position in the list that will keep the
            list in a sorted state
            NEEDS TO add UNIQUE items only!
    @param: data is a READ only reference to the original data and is copied to 
            the list
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
    @return: returns a forward_iterator to the begining of the list
    */
    iterator begin();
    const_iterator begin() const;

    /*
    @brief: creates an iterator that points to one element past the end of the 
            list dereferencing an end iterator causes undefined behavior
    @return: returns a forward iterator that points to NULL, do not dereference 
             or attempt to increment it
    */
    iterator end();
    const_iterator end() const;

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
    @return: does nothing if the list is empty.
    */
    void clear_list(Node* current);

    /*
    @brief: Travels down the list using the '<' operator to compare the data to 
            each node in the list. Stops when we find a larger element is found
            and the iterators are modified to reflect that position
    @param: data is the desired data to be added to the list, pos is the 
            position that reflects the position previous to the larger element
    @return: true if a position is found AND the data is unique
    */
    bool find_position(const_reference data, const_iterator& pos, 
                                             const_iterator& prev);

  public:

    /* Iterator */
    class forward_iterator
    {
      public:

        /* Type definitions */
        typedef typename Node::value_type      value_type;
        typedef typename Node::reference       reference;
        typedef typename Node::pointer         pointer;
        typedef forward_iterator               self_type;

        /* Constructors */

        /// @brief: default constructor points the iterator to NULL
        forward_iterator();

        /* Operator Overloads */

        /**
        @brief: prefix increment operator modifies node to point the next node in 
                a list
        @return: Returns self reference so this operation can be chained with other
                 methods
        */
        self_type& operator++(); // Prefix ++

        /**
        @brief: postfix increment operator makes a COPY of itself and then calls 
                the prefix increment operator to modify it's state
        @return: Returns a COPY of itself before incrementation
        */
        self_type& operator++(int); // Postfix ++

        /**
        @brief: * operator allows the user to inspect and mutate the data member of
                node
        @return: returns a read/write reference to the data member of a node
        */
        reference operator*();

        /**
        @brief: tests to see if each iterator is pointing to the same memory address
        @param: rhs is an iterator to be used for comparison
        @return: returns true of both rhs and this are pointing to the same address
        */
        bool operator==(const self_type& rhs) const;

        /**
        @brief: returns the logical not of the equality comparison
        @param: rhs is an iterator to be used for comparison
        */
        bool operator!=(const self_type& rhs) const;

        /* 
        Because the iterator is designed to abstract a private 
        member of the sorted list class, it is safe to make it a friend so that
        we can acces the node member when desired.
        */
       
      private:

        /** 
        @brief: value constructor points the iterator to the passed in ptr,this
                constructor is private so that the client CANNOT instantiate an
                iterator that points to an arbitrary block of memory
        @param: ptr is a pointer to a data type T
        */
        forward_iterator(pointer ptr);

        pointer node;
    };

    class const_forward_iterator : public forward_iterator
    {
       public:
        /* Type definitions */
        typedef typename Node::const_reference const_reference;
        typedef typename Node::const_pointer   const_pointer;
        typedef const_forward_iterator         self_type;

        /**
        @brief: for const qualified iterators, the * operator allows the user to 
                inspect and/or copy the value of the data member
        @return: returns a read only reference to the data member of a node
        */
        const_reference operator*() const;
    };
};

/*
Because this is a templated class, we need to include the implementation in 
the header file so the compiler can instantiate the methods with the right type 
*/
#include "linked_list.cpp"

#endif //LINKED_LIST_H
