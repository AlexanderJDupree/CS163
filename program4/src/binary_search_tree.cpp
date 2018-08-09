/*
File: binary_search_tree.cpp

Brief: Implementation file for binary search tree, b_node class and the forward
       iterator. 

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/24/2018
*/

#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP

#include "binary_search_tree.h"

// Default
template <class K, class V>
binary_tree<K, V>::binary_tree()
    : _size(0), _root(NULL) {}

// Ranged Based
template <class K, class V>
template <class key_iterator, class val_iterator>
binary_tree<K, V>::binary_tree(key_iterator key_begin, key_iterator key_end,
                               val_iterator val_begin, val_iterator val_end)
    : _size(0), _root(NULL)
{
    while(key_begin != key_end && val_begin != val_end)
    {
        insert(*key_begin++, *val_begin++);
    }
}

// Copy Constructor
template <class K, class V>
binary_tree<K, V>::binary_tree(const self_type& origin)
    : _size(0), _root(NULL)
{
    _size = copy_tree(_root, origin._root);
}

// Destructor
template <class K, class V>
binary_tree<K, V>::~binary_tree()
{
    clear();
}

template <class K, class V>
unsigned binary_tree<K, V>::copy_tree(b_node*& dest, b_node* source)
{
    if(!source)
    {
        return 0;
    }

    dest = new b_node(source->key(), source->value());

    return 1 + copy_tree(dest->left(), source->left()) 
             + copy_tree(dest->right(), source->right());

}

template <class K, class V>
binary_tree<K, V>& binary_tree<K, V>::insert(const key_type& key, 
                                             const value_type& val)
{
    insert(key, val, _root);
    ++_size;
    return *this;
}

template <class K, class V>
void binary_tree<K, V>::insert(const key_type& key, const value_type& val, 
                               b_node*& root)
{
    if(!root) // Insert at leaf
    {
        root = new b_node(key, val);
        return;
    }

    // Recursive call to find the correct position
    if(key < root->key())
    {
        return insert(key, val, root->left());
    }
    
    return insert(key, val, root->right());
}

template <class K, class V>
binary_tree<K, V>& binary_tree<K, V>::clear()
{
    delete_leaf functor;

    // Conduct postorder_traversal with a delete leaf functor
    postorder_traversal(_root, functor);

    _size = 0;
    return *this;
}

template <class K, class V>
bool binary_tree<K, V>::erase(const key_type& key)
{
    if(!_root) // Tree is empty
    {
        return false;
    }

    return erase(find(key, _root));
}

template <class K, class V>
bool binary_tree<K, V>::erase(b_node*& root)
{
    if(!root) // Key did not match a valid node
    {
        return false;
    }

    // root is a leaf
    if(!root->left() && !root->right())
    {
        delete root;
        root = NULL;
    }
    // Only right child
    else if(!root->left() && root->right())
    {
        b_node* temp = root;
        root = root->right();
        delete temp;
    }
    // Only left child
    else if(root->left() && !root->right())
    {
        b_node* temp = root;
        root = root->left();
        delete temp;
    }
    // The node has two children
    else
    {
        remove_internal_node(root, inorder_successor(root->right()));
    }

    --_size;
    return true;
}

template <class K, class V>
void binary_tree<K, V>::remove_internal_node(b_node*& root, b_node*& successor)
{
    // Copy successor
    root->key() = successor->key();
    root->value() = successor->value();


    // Adopt children
    b_node* temp = successor;
    successor = successor->right();

    // Delete successor
    delete temp;

    return;
}

template <class K, class V>
typename binary_tree<K, V>::b_node*& 
binary_tree<K, V>::inorder_successor(b_node*& node)
{
    if(!node->left())
    {
        return node;
    }

    return inorder_successor(node->left());
}

template <class K, class V>
bool binary_tree<K, V>::empty() const
{
    return !(_root);
}

template <class K, class V>
unsigned binary_tree<K, V>::size() const
{
    return _size;
}

template <class K, class V>
unsigned binary_tree<K, V>::height() const
{
    return height(_root);
}

template <class K, class V>
unsigned binary_tree<K, V>::leaves()
{
    count_leaf functor;
    
    // Traverse the tree counting each leaf
    preorder_traversal(_root, functor);

    return functor.leaves;
}

template <class K, class V>
const V& binary_tree<K, V>::root() const
{
    throw_if_null(_root, "Error in root(), root is null");

    return _root->value();
}

template <class K, class V>
const V& binary_tree<K, V>::default_object() const
{
    return _default_object;
}

template <class K, class V>
binary_tree<K, V>& binary_tree<K, V>::default_object(const value_type& obj)
{
    _default_object = obj;
    return *this;
}

template <class K, class V>
V& binary_tree<K, V>::find(const key_type& key)
{
    b_node* target = find(key, _root);

    // Find returned a valid b_node pointer
    if(target)
    {
        return target->value();
    }

    return _default_object;
}

template <class K, class V>
const V& binary_tree<K, V>::find(const key_type& key) const
{
   // Uses the logic of the non const qualified find function
   return const_cast<const V&>(const_cast<self_type&>(*this).find(key)); 
}

template <class K, class V>
typename binary_tree<K, V>::b_node*& 
binary_tree<K, V>::find(const key_type& key, b_node*& root)
{
    if(!root) // No match was found
    {
        return root; // Root is NULL
    }

    if(key == root->key()) // Match was found
    {
        return root;
    }

    if(key < root->key())
    {
        return find(key, root->left());
    }

    return find(key, root->right());
}

template <class K, class V>
typename binary_tree<K, V>::iterator binary_tree<K, V>::largest()
{
    return rbegin();
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator binary_tree<K, V>::largest() const
{
    return rbegin();
}

template <class K, class V>
typename binary_tree<K, V>::iterator binary_tree<K, V>::smallest()
{
    return begin();
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator binary_tree<K, V>::smallest() const
{
    return begin();
}

template <class K, class V>
bool binary_tree<K, V>::compare_equal(const self_type& tree) const
{
    if(_size != tree._size)
    {
        return false;
    }

    /* Iterators are used to compare the contents of the trees not 
     * the shape. A recursive algorithm would have returned false if 
     * the shapes of the trees were different, even if they shared the
     * same contents.
     */

    const_iterator left = begin();
    const_iterator right = tree.begin();

    while(left != end() && right != tree.end() && 
          *left == *right && left.key() == right.key())
    {
        ++left;
        ++right;
    }

    return left == end() && right == tree.end();
}

template <class K, class V>
typename binary_tree<K, V>::iterator binary_tree<K, V>::begin()
{
    build_traversal_queue functor(&_traversal_queue);

    inorder_traversal(_root, functor);

    return iterator(&_traversal_queue);
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator
binary_tree<K, V>::begin() const
{
    // Use the logic from the non const qualified begin()
    return const_iterator(const_cast<self_type&>(*this).begin());
}

template <class K, class V>
typename binary_tree<K, V>::iterator binary_tree<K, V>::rbegin()
{
    build_traversal_queue functor(&_traversal_queue);

    reverse_order_traversal(_root, functor);

    return iterator(&_traversal_queue);
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator
binary_tree<K, V>::rbegin() const
{
    // Use the logic from the non const qualified begin()
    return const_iterator(const_cast<self_type&>(*this).rbegin());
}

template <class K, class V>
typename binary_tree<K, V>::iterator binary_tree<K, V>::end()
{
    return iterator(NULL);
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator
binary_tree<K, V>::end() const
{
    return const_iterator(NULL);
}

template <class K, class V>
template <class Functor>
void binary_tree<K, V>::preorder_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    func(root);

    preorder_traversal(root->left(), func);

    preorder_traversal(root->right(), func);

    return;
}

template <class K, class V>
template <class Functor>
void binary_tree<K, V>::inorder_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    inorder_traversal(root->left(), func);

    func(root);

    inorder_traversal(root->right(), func);

    return;
}

template <class K, class V>
template <class Functor>
void binary_tree<K, V>::reverse_order_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    reverse_order_traversal(root->right(), func);

    func(root);

    reverse_order_traversal(root->left(), func);

    return;
}


template <class K, class V>
template <class Functor>
void binary_tree<K, V>::postorder_traversal(b_node*& root, Functor& func)
{
    if(!root)
    {
        return;
    }

    postorder_traversal(root->left(), func);

    postorder_traversal(root->right(), func);

    func(root);

    return;
}

template <class K, class V>
unsigned binary_tree<K, V>::height(b_node* root) const
{
    if(!root)
    {
        return 0;
    }

    return 1 + std::max(height(root->left()), height(root->right()));
}

template <class K, class V>
void binary_tree<K, V>::throw_if_null(b_node* node, const char* msg) const
{
    if(!node)
    {
        throw std::logic_error(msg);
    }
    return;
}

template <class K, class V>
const V& binary_tree<K, V>::operator[](const key_type& key) const
{
    return find(key);
}

template <class K, class V>
bool binary_tree<K, V>::operator == (const self_type& rhs) const
{
    return compare_equal(rhs);
}

template <class K, class V>
bool binary_tree<K, V>::operator != (const self_type& rhs) const
{
    return !(*this == rhs);
}

/****** B_NODE CLASS ******/ 

template <class K, class V>
binary_tree<K, V>::b_node::b_node(const K& key, const V& val, 
                                  b_node* left, b_node* right)
    : _key(key), _val(val), _left(left), _right(right) {}

template <class K, class V>
const K& binary_tree<K, V>::b_node::key() const
{
    return _key;
}

template <class K, class V>
K& binary_tree<K, V>::b_node::key()
{
    return _key;
}

template <class K, class V>
const V& binary_tree<K, V>::b_node::value() const
{
    return _val;
}

template <class K, class V>
V& binary_tree<K, V>::b_node::value()
{
    return _val;
}

template <class K, class V>
typename binary_tree<K, V>::b_node*& binary_tree<K, V>::b_node::left()
{
    return _left;
}

template <class K, class V>
typename binary_tree<K, V>::b_node*& binary_tree<K, V>::b_node::right()
{
    return _right;
}

/****** FORWARD ITERATOR ******/

template <class K, class V>
binary_tree<K, V>::const_iterator::const_forward_iterator(queue* traversal_state)
    : _traversal_queue(traversal_state), _ptr(NULL)
{
    if(_traversal_queue)
    {
        _traversal_queue->pop_front(_ptr);
    }
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator& 
binary_tree<K, V>::const_iterator::operator++()
{
    if(!_traversal_queue || _traversal_queue->empty())
    {
        _ptr = NULL;
    }
    else
    {
        _traversal_queue->pop_front(_ptr);
    }

    return *this;
}

template <class K, class V>
typename binary_tree<K, V>::const_iterator 
binary_tree<K, V>::const_iterator::operator++(int)
{
    const_iterator copy(*this);

    ++(*this);

    return copy;
}

template <class K, class V>
const V& binary_tree<K, V>::const_iterator::operator*() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V>
const V* binary_tree<K, V>::const_iterator::operator->() const
{
    throw_if_null();

    return &_ptr->value();
}

template <class K, class V>
const K& binary_tree<K, V>::const_iterator::key() const
{
    throw_if_null();

    return _ptr->key();
}

template <class K, class V>
const V& binary_tree<K, V>::const_iterator::value() const
{
    throw_if_null();

    return _ptr->value();
}

template <class K, class V>
bool binary_tree<K, V>::const_iterator::null() const
{
    return !(_ptr);
}

template <class K, class V>
bool binary_tree<K, V>::const_iterator::operator==(const self_type& rhs) const
{
    return _ptr == rhs._ptr;
}

template <class K, class V>
bool binary_tree<K, V>::const_iterator::operator!=(const self_type& rhs) const
{
    return !(*this == rhs);
}

template <class K, class V>
void binary_tree<K, V>::const_iterator::throw_if_null() const
{
    if(!_ptr)
    {
        throw invalid_iterator();
    }

    return;
}

template <class K, class V>
binary_tree<K, V>::iterator::forward_iterator(queue* traversal_state)
    : const_forward_iterator(traversal_state) {}

template <class K, class V>
V& binary_tree<K, V>::iterator::operator*()
{
    throw_if_null();

    return this->_ptr->value();
}

template <class K, class V>
V* binary_tree<K, V>::iterator::operator->()
{
    throw_if_null();

    return &this->_ptr->value();
}

template <class K, class V>
V& binary_tree<K, V>::iterator::value()
{
    throw_if_null();

    return this->_ptr->value();
}
template <class K, class V>
void binary_tree<K, V>::iterator::throw_if_null() const
{
    if(!this->_ptr)
    {
        throw invalid_iterator();
    }

    return;
}


#endif // BINARY_TREE_CPP

