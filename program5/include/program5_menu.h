/*
File: program5_menu.h

Brief: This file outlines the options and actions for each menu item as well as
       defines the model for the interface class

Author: Alexander DuPree

Class: CS163

Assignment: program 5

Date: 08/15/2018
*/

#include "city_graph.h"
#include "interface.h"

class add_city : public menu_item
{
  public:

    add_city(City_Graph* graph)
        : _graph(graph) {}

    const char* option() const
    {
        return "Add City";
    }

    void action()
    {
        SString city_name;

        Interface::get_input(city_name, "\nEnter the name of the City: ");

        _graph->add_city(city_name);

        std::cout << "\n\t'" << city_name << "' was added!\n";

        Interface::pause_console();

        return;
    }

  private:

    City_Graph* _graph;
};

class add_road : public menu_item
{
  public:

    add_road(City_Graph* graph)
        : _graph(graph) {}

    const char* option() const
    {
        return "Add Road";
    }

    void action()
    {
        SString start;
        SString end;
        SString road;
        int distance(0);

        Interface::get_input(road, "\nEnter the name of the road: ");
        Interface::get_input(distance, "\nEnter the length of the road: ");
        Interface::get_input(start, "\nEnter the City where the road starts: ");
        Interface::get_input(end, "\nEnter the City where the road ends: ");

        if (_graph->add_road(start, end, Road(road, distance)))
        {
            std::cout << "\n\t'" << road << "' successfully connected!"
                      << "\n\t" << start << " <---- " << distance << " miles ----> " 
                      << end << std::endl;
        }
        else
        {
            std::cout << "\n\t'" << road << "' was not connected!"
                      << "\n\tPlease ensure the start and end cities are correct\n";
                      
        }

        Interface::pause_console();

        return;
    }

  private:

    City_Graph* _graph;
};

class display_cities : public menu_item
{

  public:

    display_cities(City_Graph* graph) 
        : _graph(graph) {}

    const char* option() const
    {
        return "Display Cities";
    }

    void action()
    {
        _graph->display_cities();
        Interface::pause_console();
    }

  private:

    City_Graph* _graph;

};

class plan_roadtrip : public menu_item
{
  public:

    plan_roadtrip(City_Graph* graph)
        : _graph(graph) {}

    const char* option() const
    {
        return "Plan Roadtrip";
    }

    void action()
    {
        SString start;
        SString end;

        Interface::get_input(start, "\nEnter the starting city: ");
        Interface::get_input(end, "\nEnter the ending city: ");

        std::cout << "\nOkay here's a possible path for your roadtrip!\n";

        _graph->display_roadtrip(start, end);

        std::cout << std::endl;

        Interface::pause_console();
    }

  private:

    City_Graph* _graph;

};

class roadtrip_menu_model : public basic_model
{
  public:

    roadtrip_menu_model() 
        : basic_model(), _graph() {}

    ~roadtrip_menu_model()
    {
        clear_menu();
    }

  private:

    unsigned size() const
    {
        return SIZE;
    }

    // Instantiates the menu objects
    void build()
    {
        if (_options)
        {
            clear_menu();
        }

        build_graph();

        _options = new menu_item*[SIZE];
        _exit = new default_exit;

        _options[0] = new add_city(&_graph);
        _options[1] = new add_road(&_graph);
        _options[2] = new display_cities(&_graph);
        _options[3] = new plan_roadtrip(&_graph);
        _options[4] = _exit;
    }

    // Builds the city graph with dummy data
    void build_graph()
    {
        _graph.add_city("Portland").add_city("Vancouver").add_city("Gresham")
              .add_city("Eugene").add_city("Seaside").add_city("Sandy")
              .add_city("Seattle").add_city("Manzanita");

        _graph.add_road("Portland", "Vancouver", Road("I-5", 15));
        _graph.add_road("Portland", "Gresham", Road("I-84", 15));
        _graph.add_road("Portland", "Seaside", Road("Highway 26", 80));
        _graph.add_road("Portland", "Eugene", Road("I-5", 110));
        _graph.add_road("Gresham", "Sandy", Road("Highway 26", 12));
        _graph.add_road("Vancouver", "Seattle", Road("I-5", 168));
        _graph.add_road("Manzanita", "Seaside", Road("Highway 101", 22));

        return;
    }

    static const int SIZE = 5;

    City_Graph _graph;
};

