/*
File: city_graph.h

Description: 

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/10/2018
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

    City_Graph(unsigned size = 10);

    self_type& add_city(const string& city_name);

    bool add_road(const string& from, const string& to, const Road& road);

    void display_cities();

    void display_roadtrip(const string& from, const string& to);

  private:

    Graph<SString, Road> _graph;

    void display_cities(Graph<SString, Road>::vertex_iterator it);
};

#endif // CITY_GRAPH_H


