/*
File: city_graph.h

Description: City Graph ADT provides methods for adding cities as vertices to 
             a graph data structure as well as roads as edges for the vertices

             City Graph also comes with basic display functions to list cities
             and their edges.

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/15/2018
*/

#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include "sstring.h"
#include "graph.h"

struct Road
{
    Road(const SString& name, unsigned distance)
        : name(name), distance(distance) {}

    SString name;
    unsigned distance;
};

class City_Graph
{
  public:

    typedef SString    string;
    typedef City_Graph self_type;

    // Default Constructor
    City_Graph(unsigned size = 10);

    // Add a city to the graph structure
    self_type& add_city(const string& city_name);

    // Returns true if two cities were connected
    bool add_road(const string& from, const string& to, const Road& road);

    // Displays all cities and their direct connections
    void display_cities();

    // Displays a possible path from start to end
    void display_roadtrip(const string& from, const string& to);

  private:

    Graph<SString, Road> _graph;

    // Recursive breadth first display
    void display_cities(Graph<SString, Road>::vertex_iterator it);

    // Functor for depth first traversal
    struct roadtrip
    {
        roadtrip(SString end) : end(end) {}

        template <class Vertex>
        void operator()(Vertex* vertice)
        {
            std::cout << vertice->data();
            
            if (vertice->data() != end) 
            {
                std::cout << " -----> ";
            }

            return;
        }

        SString end;
    };
};

#endif // CITY_GRAPH_H


