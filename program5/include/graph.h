/*
File: graph.h

Description: 

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/10/2018
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"
#include "hash_table.h"

template <class V, class E>
class Graph
{

  public:

    class vertex_iterator;
    class const_vertex_iterator;

    typedef V       vertex_type;
    typedef E       edge_type;
    typedef Graph   self_type;

    /****** CONSTRUCTORS ******/

    Graph(unsigned size = 5);

    // Ranged Based Vertice Constructor
    template <class InputIterator>
    Graph(InputIterator begin, InputIterator end, unsigned size=5);
    
    ~Graph();

    /****** MODIFIERS ******/

    // Adds a vertex node to the graph
    self_type& add_vertex(const vertex_type& vertice);

    // Returns true if the vertices were successfully connected
    bool add_edge(const V& start, const V& end, const E& label, bool directed=false);

    // Clears all vertices from the graph
    self_type& clear();
    
    /****** OPERATIONS ******/
   
    // Returns true if there is a path from start to end
    bool is_connected(const vertex_type& start, const vertex_type& end);

    /****** CAPACITY ******/

    bool empty() const;
    
    // Returns the current maximum number of vertices
    unsigned max_size() const;

    // Returns the number of vertices
    unsigned vertices() const;

    // Returns the number of edges
    unsigned edges() const;

    /****** ITERATORS ******/

    vertex_iterator begin();
    const_vertex_iterator begin() const;

    vertex_iterator end();
    const_vertex_iterator end() const;

    /****** TRAVERSAL ******/

    template <class Functor>
    int depth_first(const V& start, const V& end, Functor func);

  private:

    // Forward Declaration
    class edge;

    class vertex
    {
      public:

        typedef linear_linked_list<edge>                adjacency_list;
        typedef typename adjacency_list::const_iterator adjacency_iterator;

        // Default constructor
        vertex(const vertex_type& vertice = V());

        vertex_type& data();
        const vertex_type& data() const;

        // Adds an edge to the adjacency list
        void add_edge(vertex* dest, const E& label);

        adjacency_iterator begin() const;
        adjacency_iterator end() const;

      private:

        vertex_type _data;

        adjacency_list _adjacencies;
    };

    class edge
    {
      public:

          edge(vertex* start, vertex* end, const edge_type& data=E());

          edge_type& data();
          const edge_type& data() const;

          vertex*& from();
          vertex*  from() const;

          vertex*& to();
          vertex*  to() const;

      private:

          vertex* _from;
          vertex* _to;

          edge_type _data;
    };

    typedef hash_table<vertex*, bool> history;

    unsigned _size; // Maximum number of vertices the graph can store
    unsigned _vertex_count; // The number of vertices on the graph
    unsigned _edge_count; // The number of edges on the graph
    vertex* _vertices; // Table of vertices

    /****** FUNCTORS ******/
    struct is_null
    {
        bool operator()(vertex* vertice) { return !vertice; }
    };

    /****** SUBROUTINES ******/

    // Triggered when vertex_count is equal to the _size, copies and doubles table
    void resize();

    // Returns a pointer to the matching vertex
    vertex* find(const vertex_type& key) const;

    /****** TRAVERSAL ******/
    template <class Functor>
    int depth_first(vertex* from, vertex* to, Functor func, history&);

  public:
    
    /****** ITERATOR CLASSS ******/
    class vertex_iterator
    {
      public:

        typedef vertex_iterator self_type;
        typedef typename vertex::adjacency_iterator adjacency_iterator;

        // Default Constructor
        vertex_iterator(vertex* ptr=NULL)
            : _ptr(ptr) {}

        // Increment Operators
        self_type& operator++();
        self_type& operator++(int);

        // Dereference Operators
        vertex_type& operator*();
        vertex_type* operator->();

        // Adjacency_iterators
        adjacency_iterator begin() const;
        adjacency_iterator end() const;

        // Null check
        bool null() const;

        // Equality operators
        bool operator==(const self_type& rhs) const;
        bool operator!=(const self_type& rhs) const;

      protected:

        void throw_if_null() const;

        vertex* _ptr;
    };

    class const_vertex_iterator : public vertex_iterator
    {
      public:

        const_vertex_iterator(vertex* ptr=NULL)
            : vertex_iterator(ptr) {}

        // Dereference Operators
        const vertex_type& operator*() const;
        const vertex_type* operator->() const;

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

#include "graph.cpp"

#endif // GRAPH_H

