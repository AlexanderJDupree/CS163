/*
File: binary_search_tree.h

Brief: Binary search tree is a tree based data strucutre. This implementation of 
       the BST provides methods for insertion, erasure, search, and mutation of
       key/value pairs. This BST is a fully templated class that contains 
       iterator functionality as well as diagnostic methods such as calculating
       the tree's height and leaves.

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

template<class K, class V>
class binary_tree
{
    class b_node;

  public:

    class forward_iterator;
    class const_forward_iterator;

    typedef K                             key_type;
    typedef V                             value_type;
    typedef binary_tree                   self_type;
    typedef circular_linked_list<b_node*> queue;
    typedef forward_iterator              iterator;
    typedef const_forward_iterator        const_iterator;
    
    /****** CONSTRUCTORS ******/

    // Default Constructor
    binary_tree();

    // Range Based Constructor
    template <class key_iterator, class val_iterator>
    binary_tree(key_iterator key_begin, key_iterator key_end,
                val_iterator val_begin, val_iterator val_end);

    // Copy Constructor
    binary_tree(const self_type& origin);

    ~binary_tree();

    /****** MODIFIERS ******/

    // Inserts the data at a leaf
    self_type& insert(const key_type& key, const value_type& value);

    // Erases the data from the tree
    bool erase(const key_type& key);

    // Clears the BST
    self_type& clear();

    /****** CAPACITY ******/

    // Returns true if the tree is empty
    bool empty() const;

    // Returns the number of elements on the table
    unsigned size() const;

    /****** ITERATORS ******/

    iterator begin();
    const_iterator begin() const;

    iterator rbegin();
    const_iterator rbegin() const;

    iterator end();
    const_iterator end() const;

    /****** OPERATIONS ******/

    // Returns the root's value
    const value_type& root() const;

    // Sets the default return object
    self_type& default_object(const value_type& obj);

    // Returns the default object
    const value_type& default_object() const;

    // Returns the matching object
    value_type& find(const key_type& key);
    const value_type& find(const key_type& key) const;

    // Returns a reverse iterator to the largest element.
    iterator largest();
    const_iterator largest() const;

    // Returns an iterator to the smallest element
    iterator smallest();
    const_iterator smallest() const;

    // Returns true if the trees share the same contents, not necessarily the 
    // same shape.
    bool compare_equal(const self_type& tree) const;

    /****** DIAGNOSTICS ******/

    // Returns the height of the tree
    unsigned height() const;

    // Returns the number of leaves
    unsigned leaves();

    /****** OEPRATORS ******/

    // Returns an object with the matching key
    const value_type& operator[](const key_type& key) const;

    // Equality operators return the result of compare_equal
    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;

  private:

    class b_node
    {
      public:

        b_node(const K& key = K(), const V& val = V(), 
               b_node* left = NULL, b_node* right = NULL);

        const key_type& key() const;
        key_type& key();

        const value_type& value() const;
        value_type& value();

        b_node*& left();
        b_node*& right();

      private:

        key_type   _key;
        value_type _val;

        b_node* _left;
        b_node* _right;
    };

    unsigned _size; // The number of elements in the tree
    b_node* _root; // Root node
    value_type _default_object; // Default object is return on failed searches

    queue _traversal_queue; // Stores the inorder traversal state into a queue, 
                            // The iteratros utilize the queue to traverse to the
                            // correct node

    /****** SUBROUTINES ******/

    void throw_if_null(b_node* node, const char* msg="b_node* points to null") const;

    void remove_internal_node(b_node*& root, b_node*& successor);

    /****** RECURSIVE HELPERS ******/

    // Returns the numbner of nodes copied
    unsigned copy_tree(b_node*& dest, b_node* source);

    // Inserts the data at a leaf
    void insert(const key_type& key, const value_type& val, b_node*& root);

    // Returns the data matching the key, or the default object
    b_node*& find(const key_type& key, b_node*& root);

    // Finds the inorder successor, initial call with node->right()
    b_node*& inorder_successor(b_node*& root);

    // Deletes the node pointed to by root
    bool erase(b_node*& root);

    // Returns the height of the tree 
    unsigned height(b_node* root) const;

    /****** TRAVERSAL ALGORITHMS ******/

    // Traversal functions traverse the tree applying the functor to each node

    template <class Functor>
    void preorder_traversal(b_node*& root, Functor& funct);

    template <class Functor>
    void inorder_traversal(b_node*& root, Functor& func);

    template <class Functor>
    void reverse_order_traversal(b_node*& root, Functor& func);

    template <class Functor>
    void postorder_traversal(b_node*& root, Functor& func);
    
    struct build_traversal_queue
    {
        build_traversal_queue(queue* ptr) 
            : _traversal_queue(ptr) 
        {
            _traversal_queue->clear();
        }

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

    struct count_leaf
    {
        count_leaf() : leaves(0) {}

        void operator()(b_node* node)
        {
            if(!node->left() && !node->right())
            {
                ++leaves;
            }
            return;
        }

        int leaves;
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
        self_type  operator++(int);

        // Dereference Operators
        const value_type& operator*() const;
        const value_type* operator->() const;

        // Key/Value access
        const key_type& key() const;
        const value_type& value() const;

        // Null check
        bool null() const;

        // Equality operators
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;

      protected:

        void throw_if_null() const;

        queue* _traversal_queue;

        b_node* _ptr;
    };

    class forward_iterator : public const_forward_iterator
    {
      public:

          typedef forward_iterator self_type;

          // Default Constructor
          forward_iterator(queue* traversal_state=NULL);

          // Dereference Operators;
          value_type& operator*();
          value_type* operator->();

          // Value access only
          value_type& value();

      private:

        void throw_if_null() const;
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

