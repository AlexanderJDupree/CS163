/*
File: city_graph.cpp

Description: Implementation file for the city_graph ADT. Operates as a wrapper 
             class for the underlying Graph data structure

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/15/2018
*/

#include "city_graph.h"

City_Graph::City_Graph(unsigned size)
    : _graph(size) {}

City_Graph& City_Graph::add_city(const string& city_name)
{
    _graph.add_vertex(city_name);
    return *this;
}

bool City_Graph::add_road(const string& from, const string& to, const Road& road)
{
    return _graph.add_edge(from, to, road);
}

void City_Graph::display_cities()
{
    std::cout << "\t\t\tCITIES\n" << SString(57, '=');

    Graph<SString, Road>::vertex_iterator it = _graph.begin();

    display_cities(it);

}

void City_Graph::display_cities(Graph<SString, Road>::vertex_iterator it)
{
    if (it == _graph.end())
    {
        return;
    }

    std::cout << "\n\t\t" << *it << '\n' << SString(40, '-');

    Graph<SString, Road>::vertex_iterator::adjacency_iterator iter;
    for(iter = it.begin(); iter != it.end(); ++iter)
    {
        std::cout << '\n' << iter->data().name << ", " << iter->data().distance 
                  << " miles ------> " << iter->to()->data() << '\n';
    }
    std::cout << std::endl;

    display_cities(++it);
}

void City_Graph::display_roadtrip(const string& from, const string& to)
{
    std::cout << "\n\tRoadtrip from " << from << " to " << to << '\n' 
              << SString(57, '-') << '\n';

    roadtrip functor(to);

    if(!_graph.depth_first(to, from, functor))
    {
        std::cout << "\nSorry, looks like those cities aren't connected\n";
    }

    return;
}

