/*
File: interface.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
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
    virtual const char* option() const = 0;
    virtual void action() = 0;
};

class menu_model
{
  public:
    virtual ~menu_model() {}
    virtual unsigned size() const = 0;
    virtual void build(menu_item**& menu) = 0;
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

    Interface(menu_model* model = NULL);

    ~Interface();

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

  private:

    menu_model* _model;

    const unsigned OPTION_COUNT;

    menu_item** _options;

    exit_application _exit; // Default menu option to exit application

    // Clears fail flags, flushes input buffer
    static void reset_input_stream();
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
