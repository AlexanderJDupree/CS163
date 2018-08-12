/*
File: graph_tests.cpp

Description: Unit tests

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/10/2018
*/

#include "catch.hpp"
#include "sstring.h"
#include "graph.h"

TEST_CASE("Constructing graphs", "[graph], [constructor]")
{
    SECTION("Default Construction")
    {
        Graph<char*, int> graph;

        REQUIRE(graph.empty());
        REQUIRE(graph.max_size() == 5);
    }
    SECTION("Ranged based vertice construction")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV", "DLS" };

        Graph<SString, int> graph(airports, airports + 6);

        REQUIRE(graph.vertices() == 6);
        REQUIRE(graph.max_size() == 10);
    }
}

TEST_CASE("Adding vertices to a graph", "[graph], [add_vertex]")
{
    SECTION("Adding a vertex to an empty graph")
    {
        Graph<SString, int> graph;

        graph.add_vertex("PDX");

        REQUIRE(graph.vertices() == 1);
    }
    SECTION("Adding more vertexes than the size of the graph triggers resize")
    {
        Graph<SString, int> graph(3);

        graph.add_vertex("PDX").add_vertex("LAX").add_vertex("PHX").add_vertex("CHI");

        REQUIRE(graph.vertices() == 4);
        REQUIRE(graph.max_size() == 6);
    }
}

TEST_CASE("Adding edges to vertices")
{
    SECTION("Adding a non-directed edge")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        REQUIRE(graph.add_edge("PDX", "LAX", 7));
        REQUIRE(graph.is_connected("LAX", "PDX"));
        REQUIRE(graph.edges() == 1);
    }
    SECTION("Adding a directed edge")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);
        
        REQUIRE(graph.add_edge("PHX", "CHI", 7, true));
        REQUIRE(graph.is_connected("PHX", "CHI"));
        REQUIRE_FALSE(graph.is_connected("CHI", "PHX"));
    }
}

TEST_CASE("Iterating through all vertices")
{
    SECTION("A populated graph")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        unsigned i = 0;
        Graph<SString, int>::vertex_iterator it;
        for(it = graph.begin(); it != graph.end(); ++it)
        {
            REQUIRE(*it == airports[i++]);
        }
    }
    SECTION("A const qualified graph")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        const Graph<SString, int> graph(airports, airports + 5);

        unsigned i = 0;
        Graph<SString, int>::const_vertex_iterator it;
        for(it = graph.begin(); it != graph.end(); ++it)
        {
            REQUIRE(*it == airports[i++]);
        }
    }
    SECTION("An empty graph")
    {
        Graph<int, int> graph;

        REQUIRE(graph.begin() == graph.end());
    }
}

