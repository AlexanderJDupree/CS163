/*
File: interface.cpp

Description: Implementation file for the Interface class

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 06/27/2018
*/

#include "interface.h"

// Default constructor calls the factory build method to instantiate the correct
// model for the menu
Interface::Interface(model_factory* factory)
    : _model(factory->build_model()), _option_count(_model->size()), 
      _options(NULL) {}

Interface::~Interface()
{
    clear_menu();

    delete _model;
}

void Interface::clear_menu()
{
    // The _options member is an array of menu_item pointers and requires an 
    // iterative delete cycle to prevent memory leaks
    for (unsigned i = 0; i < _option_count; ++i)
    {
        delete _options[i];
        _options[i] = NULL;
    }

    delete [] _options;

    _options = NULL;
}

void Interface::build()
{
    // We want to clear the menu before we build a new one
    if (_options)
    {
        clear_menu();
    }

    // Ensure the model has been instantiated
    if (_model)
    {
        _model->build(_options);
    }
    return;
}

void Interface::display_menu() const
{
    // Loops through each menu option and calls the option() method to print 
    // the menu in a formatted fashion.
    std::cout << "=========================================================\n";
    int count = 1;
    for (unsigned i = 0; i < _option_count; ++i)
    {
        std::cout << "\n  " << count++ << ".\t" 
                  << _options[i]->option() << std::endl;
    }
    std::cout << "\n  " << count << ".\t" << _exit.option() << std::endl;
    std::cout << "\n=========================================================\n";
    return;
}

void Interface::run_action(unsigned index)
{
    if (--index == _option_count)
    {
        _exit.action();
        return;
    }

    if (index > _option_count)
    {
        display_error("\n\tInvalid selection, please try again.\n");
        return;
    }

    _options[index]->action();
    return;
}

void Interface::run()
{
    unsigned input(0);
    while(!_exit())
    {
        display_menu();

        run_action(Interface::get_input("\n>", input));
    }

    return;
}

void Interface::display_error(const char* message)
{
    std::cout << message << std::endl;
    return;
}

void Interface::reset_input_stream()
{
    // reset failed state
    std::cin.clear();

    // discard characters up to the limit of the stream OR to newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}
