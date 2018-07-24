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

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <limits>
#include <iostream>
#include "menu.h"

class Interface
{
  public:

    // If a model is specified, it will build that model.
    Interface(menu_model* model = NULL, model_viewer* view = NULL);

    ~Interface() {};

    // Replaces the current model with the specified model and builds it
    void build(menu_model* model = NULL);

    // Loops through the options and prints the options string
    void display_menu() const;

    // Runs the action mapped to the menu's index
    void run_action(unsigned index);

    // prints menu, evaluates input, runs action. loops until exit is selected
    void run();

    const menu_model* view_model() const;

    // Takes in an out parameter and OVERRIDES it with user input
    template <typename T>
    static T& get_input(T& out_param, const char* prompt = "\n> ");

    template <typename T>
    static T get_input(const char* prompt = "\n> ");

    static void pause_console(const char* prompt = "\nPress ENTER to continue\n");

    static bool repeat_loop(const char* prompt = "\nAgain? Y/N: ");

    static void clear_screen();

    // Prints message to the console
    static void display_error(const char* message);

  private:

    menu_model* _model; // The model that builds and connects the menu options
    model_viewer* _view;

    basic_model _default_model;
    basic_view _default_viewer;

    // Clears fail flags, flushes input buffer
    static void reset_input_stream();

};

template <typename T>
T& Interface::get_input(T& out_param, const char* prompt)
{
    std::cout << prompt;
    std::cin >> out_param;

    reset_input_stream();

    return out_param;
}

template <typename T>
T Interface::get_input(const char* prompt)
{
    T input;

    std::cout << prompt;
    std::cin >> input;

    reset_input_stream();

    return input;
}

#endif // INTERFACE_H
