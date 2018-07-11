/*
File: interface.h

Description: Interface class acts as the command line interface manager for any
             application.

             The Interface utilizes the menu_items abstract base class to map
             an option to an action in the menu. The implementation of these 
             menu_items is unknown to the Interface and requires a menu_model to
             instantiate and connect the menu_options to their required 
             dependencies. 

             Again, the implementation of the model is undefined 
             and requires the model_factory to direct the Interface to instantiate
             the correct model to build the menu.

             Interface comes default with the exit_application menu option. 
             exit_application will appear at the bottom of the menu and 
             terminates the run() loop when selected.

             Interface also comes with a templated static method to grab input 
             from the console. get_input will takes in any object as an 
             out_paramter and then overrides the objects data with the keyboard
             input.

Author: Alexander DuPree

Date: 07/11/2018
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <limits>
#include <iostream>

// Abstract base class for all menu options in the interface
class menu_item
{
  public:
    virtual ~menu_item() {}
    
    // Returns the menu option caption
    virtual const char* option() const = 0;

    // Executes the action mapped to the option
    virtual void action() = 0;
};

// The model is used to build and connect all menu_items into the interface
class menu_model
{
  public:
    virtual ~menu_model() {}
    
    // Returns the number of options in the menu
    virtual unsigned size() const = 0;

    // Instantiated the menu items with their dependencies onto the Interface
    virtual void build(menu_item**& menu) = 0;
};

// The factory builds and returns the correct model for the interface to use
class model_factory
{
  public:
    virtual ~model_factory() {}

    // Returns a new menu_model
    virtual menu_model* build_model() = 0;
};

// exit_application is the default menu_option in the interface class
struct exit_application : public menu_item
{
    bool exit;

    exit_application() : exit(false) {}

    bool operator()() { return exit; }

    const char* option() const { return "Exit Application"; }

    void action() 
    { 
        std::cout << "\n\tHave a nice day!\n";
        exit = true; 
    }
};

class Interface
{
  public:

    // Default construction requires a factory to construct the correct model
    // for the menu. 
    Interface(model_factory* factory);

    ~Interface();

    // Tells the model to build the menu options
    void build();

    // Loops through the options and prints the options string
    void display_menu() const;

    // Runs the action mapped to the menu's index
    void run_action(unsigned index);

    // prints menu, evaluates input, runs action. loops until exit is selected
    void run();

    // Takes in an out parameter and OVERRIDES it with user input
    template <typename T>
    static T& get_input(const char* prompt, T& out_param);

    // Prints message to the console
    static void display_error(const char* message);

  private:

    menu_model* _model; // The model that builds and connects the menu options

    unsigned _option_count; // The number of menu options

    menu_item** _options; // An array of menu_item pointers represents the menu

    exit_application _exit; // Default menu option to exit application

    // Clears fail flags, flushes input buffer
    static void reset_input_stream();

    // Loops through the options and deletes each menu item
    void clear_menu(); 
};

template <typename T>
T& Interface::get_input(const char* prompt, T& out_param)
{
    std::cout << prompt;
    std::cin >> out_param;

    reset_input_stream();

    return out_param;
}

#endif // INTERFACE_H
