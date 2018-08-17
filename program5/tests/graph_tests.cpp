/*
File: graph_tests.cpp

Description: Unit tests for the graph data structure

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

TEST_CASE("Adding edges to vertices", "[graph], [add_edge]")
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

TEST_CASE("Determining if two vertices are connected", "[graph], [connected], [dfs]")
{
    SECTION("A direct connection")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        REQUIRE(graph.add_edge("PDX", "LAX", 7));
        REQUIRE(graph.is_connected("LAX", "PDX"));
    }
    SECTION("An indirect connection")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        REQUIRE(graph.add_edge("PDX", "LAX", 7));
        REQUIRE(graph.add_edge("LAX", "CHI", 9));
        REQUIRE(graph.add_edge("CHI", "PHX", 6));
        REQUIRE(graph.is_connected("PDX", "PHX"));
        REQUIRE_FALSE(graph.is_connected("PDX", "CLV"));
    }
}

TEST_CASE("Iterating through all vertices", "[graph], [iterators]")
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

TEST_CASE("Iterating through adjacencies")
{
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        graph.add_edge("PDX", "LAX", 1);
        graph.add_edge("PDX", "PHX", 2);
        graph.add_edge("PDX", "CHI", 3);

        int i = 0;
        Graph<SString, int>::vertex_iterator::adjacency_iterator it;
        for(it = graph.begin().begin(); it != graph.begin().end(); ++it)
        {
            REQUIRE(it->data() == ++i);
        }
}

TEST_CASE("Clearing a graph", "[graph], [clear]")
{
    SECTION("A populated graph")
    {
        SString airports[] = { "PDX", "LAX", "PHX", "CHI", "CLV" };

        Graph<SString, int> graph(airports, airports + 5);

        REQUIRE(graph.clear().vertices() == 0);
        REQUIRE(graph.edges() == 0);
    }
}
