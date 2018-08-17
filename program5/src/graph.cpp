/*
File: graph.cpp

Description: Implementation file for the graph class

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/15/2018
*/

#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"

template <class V, class E>
Graph<V, E>::Graph(unsigned size)
    : _size(size), _vertex_count(0), _edge_count(0), 
      _vertices(new vertex[_size]) {}

template <class V, class E>
template <class InputIterator>
Graph<V, E>::Graph(InputIterator begin, InputIterator end, unsigned size)
    : _size(size), _vertex_count(0), _edge_count(0), _vertices(new vertex[_size])
{
    for(; begin != end; ++begin)
    {
        add_vertex(*begin);
    }
}

template <class V, class E>
Graph<V,E>::~Graph()
{
    delete [] _vertices;
}

template <class V, class E>
Graph<V, E>& Graph<V, E>::add_vertex(const vertex_type& vertice)
{
    if(_vertex_count >= _size)
    {
        resize();
    }
    
    _vertices[_vertex_count++] = vertex(vertice);
   
    return *this;
}

template <class V, class E>
bool Graph<V, E>::add_edge(const V& start, const V& end, const E& label, bool directed)
{
    vertex* _start = find(start);
    vertex* _end = find(end);

    if(!_start || !_end) // Checks if the vertices exist on the graph
    {
        return false;
    }

    _start->add_edge(_end, label);
    
    if(!directed)
    {
        _end->add_edge(_start, label);
    }

    ++_edge_count;
    return true;
}

template <class V, class E>
Graph<V,E>& Graph<V,E>::clear()
{
    delete [] _vertices;
    _vertices = new vertex[_size];
    _vertex_count = 0;
    _edge_count = 0;
    return *this;
}

template <class V, class E>
bool Graph<V,E>::is_connected(const V& start, const V& end)
{
    return depth_first(start, end, is_null());
}

template <class V, class E>
typename Graph<V, E>::vertex* Graph<V,E>::find(const vertex_type& key) const
{
    for(vertex* v = _vertices; v != _vertices + _vertex_count; ++v)
    {
        if (v->data() == key)
        {
            return v;
        }
    }
    return NULL;
}

template <class V, class E>
void Graph<V, E>::resize()
{
    vertex* temp = new vertex[_size * 2];
    for (unsigned i = 0; i < _size; ++i)
    {
        temp[i] = _vertices[i];
    }

    delete [] _vertices;
    _vertices = temp;
    _size *= 2;
    return;
}

template <class V, class E>
bool Graph<V,E>::empty() const
{
    return _vertex_count == 0;
}

template <class V, class E>
unsigned Graph<V,E>::max_size() const
{
    return _size;
}

template <class V, class E>
unsigned Graph<V,E>::vertices() const
{
    return _vertex_count;
}

template <class V, class E>
unsigned Graph<V,E>::edges() const
{
    return _edge_count;
}

template <class V, class E>
typename Graph<V, E>::vertex_iterator Graph<V, E>::begin()
{
    return vertex_iterator(_vertices);
}

template <class V, class E>
typename Graph<V, E>::const_vertex_iterator Graph<V, E>::begin() const
{
    return const_vertex_iterator(_vertices);
}

template <class V, class E>
typename Graph<V, E>::vertex_iterator Graph<V, E>::end()
{
    return vertex_iterator(_vertices + _vertex_count);
}

template <class V, class E>
typename Graph<V, E>::const_vertex_iterator Graph<V, E>::end() const
{
    return const_vertex_iterator(_vertices + _vertex_count);
}

template <class V, class E>
template <class Functor>
int Graph<V, E>::depth_first(const V& start, const V& end, Functor func)
{
    vertex* _start = find(start);
    vertex* _end = find(end);

    if(!_start || !_end)
    {
        return 0;
    }

    // Keeps track of what nodes have been visited
    history visited;
    visited.default_object(false);

    return depth_first(_start, _end, func, visited);
}

template <class V, class E>
template <class Functor>
int Graph<V, E>::depth_first(vertex* start, vertex* end, Functor func, 
                                                         history& visited)
{
    if (visited[start])
    {
        return 0;
    }

    visited[start] = true;

    // Destination Reached
    if(start == end)
    {
        func(start);
        return 1;
    }

    int path = 0;
    typename vertex::adjacency_iterator it;
    for (it = start->begin(); it != start->end(); ++it)
    {
        path += depth_first(it->to(), end, func, visited);
        if(path)
        {
            func(start);
            return path;
        }
    }
    return 0;
}

/****** VERTEX CLASS ******/

template <class V, class E>
Graph<V,E>::vertex::vertex(const vertex_type& vertex)
    : _data(vertex) {}

template <class V, class E>
V& Graph<V,E>::vertex::data()
{
    return _data;
}

template <class V, class E>
const V& Graph<V,E>::vertex::data() const
{
    return _data;
}

template <class V, class E>
void Graph<V,E>::vertex::add_edge(vertex* dest, const E& label)
{
    _adjacencies.push_back(edge(this, dest, label));
    return;
}

template <class V, class E>
typename Graph<V, E>::vertex::adjacency_iterator 
Graph<V,E>::vertex::begin() const
{
    return _adjacencies.begin();
}

template <class V, class E>
typename Graph<V, E>::vertex::adjacency_iterator 
Graph<V,E>::vertex::end() const
{
    return _adjacencies.end();
}

/****** EDGE CLASS ******/

template <class V, class E>
Graph<V,E>::edge::edge(vertex* from, vertex* to, const edge_type& data)
    : _from(from), _to(to), _data(data) {}

template <class V, class E>
E& Graph<V,E>::edge::data()
{
    return _data;
}

template <class V, class E>
const E& Graph<V,E>::edge::data() const
{
    return _data;
}

template <class V, class E>
typename Graph<V,E>::vertex*& Graph<V,E>::edge::from() 
{
    return _from;
}

template <class V, class E>
typename Graph<V,E>::vertex* Graph<V,E>::edge::from() const
{
    return _from;
}

template <class V, class E>
typename Graph<V,E>::vertex*& Graph<V,E>::edge::to() 
{
    return _to;
}

template <class V, class E>
typename Graph<V,E>::vertex* Graph<V,E>::edge::to() const
{
    return _to;
}

/****** VERTEX_ITERATOR ******/

template <class V, class E>
typename Graph<V, E>::vertex_iterator& 
Graph<V, E>::vertex_iterator::operator++()
{
    ++_ptr;
    return *this;
}

template <class V, class E>
typename Graph<V, E>::vertex_iterator& 
Graph<V, E>::vertex_iterator::operator++(int)
{
    self_type copy = self_type(*this);
    ++(*this);
    return copy;
}

template <class V, class E>
V& Graph<V, E>::vertex_iterator::operator*()
{
    throw_if_null();

    return _ptr->data();
}

template <class V, class E>
V* Graph<V, E>::vertex_iterator::operator->()
{
    throw_if_null();

    return &_ptr->data();
}

template <class V, class E>
typename Graph<V,E>::vertex_iterator::adjacency_iterator
Graph<V,E>::vertex_iterator::begin() const
{
    return _ptr->begin();
}

template <class V, class E>
typename Graph<V,E>::vertex_iterator::adjacency_iterator
Graph<V,E>::vertex_iterator::end() const
{
    return _ptr->end();
}

template <class V, class E>
bool Graph<V, E>::vertex_iterator::null() const
{
    return !(_ptr);
}

template <class V, class E>
bool Graph<V, E>::vertex_iterator::operator==(const self_type& rhs) const
{
    return _ptr == rhs._ptr;
}

template <class V, class E>
bool Graph<V, E>::vertex_iterator::operator!=(const self_type& rhs) const
{
    return _ptr != rhs._ptr;
}

template <class V, class E>
void Graph<V,E>::vertex_iterator::throw_if_null() const
{
    if(_ptr)
    {
        return;
    }

    throw invalid_iterator();
}

template <class V, class E>
const V& Graph<V, E>::const_vertex_iterator::operator*() const
{
    throw_if_null();

    return this->_ptr->data();
}

template <class V, class E>
const V* Graph<V, E>::const_vertex_iterator::operator->() const
{
    throw_if_null();

    return &this->_ptr->data();
}

template <class V, class E>
void Graph<V,E>::const_vertex_iterator::throw_if_null() const
{
    if(this->_ptr)
    {
        return;
    }

    throw invalid_iterator();
}

#endif // GRAPH_CPP

