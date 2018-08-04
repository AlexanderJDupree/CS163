/*
File: binary_search_tree.h

Brief: 

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/24/2018
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef> // NULL
#include <algorithm> // std::max
#include <stdexcept> // std::logic_error
#include "circular_list.h" 

template<class T>
class binary_tree
{
    class b_node;

  public:

    class const_forward_iterator;

    typedef T                             value_type;
    typedef T&                            reference;
    typedef const T&                      const_reference;
    typedef T*                            pointer;
    typedef const T*                      const_pointer;
    typedef binary_tree                   self_type;
    typedef circular_linked_list<b_node*> queue;
    typedef const_forward_iterator        const_iterator;
    
    /****** CONSTRUCTORS ******/

    // Default Constructor
    binary_tree();

    // Range Based Constructor
    template <class InputIterator>
    binary_tree(InputIterator begin, InputIterator end);

    ~binary_tree();

    /****** MODIFIERS ******/

    // Inserts the data at a leaf
    self_type& insert(const_reference data);

    // Clears the BST
    self_type& clear();

    /****** CAPACITY ******/

    // Returns true if the tree is empty
    bool empty() const;

    // Returns the number of elements on the table
    unsigned size() const;

    /****** ITERATORS ******/

    const_iterator begin();
    const_iterator end();

    /****** OPERATIONS ******/

    // Returns the root's value
    const_reference root() const;

    // Sets the default return object
    self_type& default_object(const_reference obj);

    // Returns the default object
    const_reference default_object() const;

    // Returns the matching object
    const_reference find(const_reference key) const;

    /****** DIAGNOSTICS ******/

    // Returns the height of the tree
    unsigned height() const;

  private:

    class b_node
    {
      public:

        b_node(const T& data = T(), b_node* left = NULL, b_node* right = NULL);

        const_reference data() const;

        b_node*& left();
        b_node*& right();

      private:

        value_type _data;

        b_node* _left;
        b_node* _right;
    };

    unsigned _size; // The number of elements in the tree
    b_node* _root; // Root node
    value_type _default_object; // Default object is return on failed searches
    queue _traversal_queue;

    /****** SUBROUTINES ******/

    void throw_if_null(b_node* node, const char* msg="b_node* points to null") const;

    /****** RECURSIVE HELPERS ******/

    void insert(const_reference data, b_node*& root);
    const_reference find(const_reference key, b_node* root) const;
    unsigned height(b_node* root) const;

    /****** TRAVERSAL ALGORITHMS ******/
    template <class Functor>
    void inorder_traversal(b_node*& root, Functor& func);

    template <class Functor>
    void postorder_traversal(b_node*& root, Functor& func);
    
    struct build_traversal_queue
    {
        build_traversal_queue(queue* ptr) 
            : _traversal_queue(ptr) {}

        void operator()(b_node* root)
        {
            _traversal_queue->push_back(root);
        }

        queue* _traversal_queue;
    };

    struct delete_leaf
    {
        void operator()(b_node*& leaf)
        {
            delete leaf;
            leaf = NULL;
            return;
        }
    };

  public:

    class const_forward_iterator 
    {
      public:

        typedef const_forward_iterator self_type;

        // Default Constructor
        const_forward_iterator(queue* traversal_state=NULL);

        // Increment Operators
        self_type& operator++();
        self_type& operator++(int);

        // Dereference Operators
        const_reference operator*() const;
        const_pointer operator->() const;

        // Null check
        bool null() const;

        // Equality operators
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;

      private:

        void throw_if_null() const;

        queue* _traversal_queue;

        b_node* _ptr;
    };

    // Custom Exception for Iterator class
    struct invalid_iterator : public std::exception
    {
        const char* _error;

        invalid_iterator(const char* error = "invalid iterator: points to NULL")
            : _error(error) {}
        
        const char* what() const throw()
        {
            return _error;
        }
    };
};

#include "binary_search_tree.cpp"

#endif // BINARY_TREE_H

