/*
File: graph.cpp

Description: Implementation file for the graph class

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/10/2018
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"

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
    
    /****** MODIFIERS ******/

    self_type& add_vertex(const vertex_type& vertice);

    bool add_edge(const V& from, const V& to, const E& label, bool directed=false);
    
    /****** OPERATIONS ******/
   
    bool is_connected(const vertex_type& from, const vertex_type& to) const;

    /****** CAPACITY ******/

    bool empty() const;
    unsigned max_size() const;
    unsigned vertices() const;
    unsigned edges() const;

    /****** ITERATORS ******/

    vertex_iterator begin();
    const_vertex_iterator begin() const;

    vertex_iterator end();
    const_vertex_iterator end() const;

  private:

    // Forward Declaration
    class edge;

    class vertex
    {
      public:

        typedef linear_linked_list<edge>                adjacency_list;
        typedef typename adjacency_list::const_iterator adjacency_iterator;

        vertex(const vertex_type& vertice = V());

        vertex_type& data();
        const vertex_type& data() const;

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

          edge(vertex* from, vertex* to, const edge_type& data=E());

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

    unsigned _size;
    unsigned _vertex_count;
    unsigned _edge_count;
    vertex* _vertices;

    /****** SUBROUTINES ******/
    void resize();

    vertex* find(const vertex_type& key) const;

  public:
    
    /****** ITERATOR CLASSS ******/
    class vertex_iterator
    {
      public:

        typedef vertex_iterator self_type;

        // Default Constructor
        vertex_iterator(vertex* ptr=NULL)
            : _ptr(ptr) {}

        // Increment Operators
        self_type& operator++();
        self_type& operator++(int);

        // Dereference Operators
        vertex_type& operator*();
        vertex_type* operator->();

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

