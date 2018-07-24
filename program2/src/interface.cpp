/*
File: interface.cpp

Description: Implementation file for the Interface class

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 06/27/2018
*/

#include "interface.h"

Interface::Interface(menu_model* model, model_viewer* view)
    : _model(model), _view(view) 
{
    if(!_model)
    {
        _model = &_default_model;
    }
    if (!_view)
    {
        _view = &_default_viewer;
    }

    build(_model);
}

void Interface::build(menu_model* model)
{
    // If the new model has been specified, overwrite
    if (model)
    {
        _model = model;
    }

    // Ensure the model member isn't NULL
    if(_model)
    {
        _model->build();
    }

    return;
}

void Interface::display_menu() const
{
    _view->draw(_model);

    return;
}

void Interface::run_action(unsigned index)
{
    try
    {
        _model->option(--index)->action();
    }
    catch (const std::logic_error& err)
    {
        display_error("\n\tInvalid selection, try again.\n");
        pause_console();
    }
    return;
}

const menu_model* Interface::view_model() const
{
    return _model;
}

void Interface::run()
{
    if (!_model)
    {
        throw std::logic_error("Interface was not provided a model");
    }

    while(!_model->exit())
    {
        display_menu();

        run_action(get_input<unsigned>());
    }

    return;
}

void Interface::display_error(const char* message)
{
    std::cout << message << std::endl;
    return;
}

void Interface::pause_console(const char* prompt)
{
    std::cout << prompt;
    std::cin.get();
    return;
}

bool Interface::repeat_loop(const char* prompt)
{
    std::cout << prompt;
    return std::tolower(get_input<char>("\n> ")) ==  'y';
}

void Interface::clear_screen() 
{
    std::cout << std::string(100, '\n');
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
