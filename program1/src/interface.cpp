/*
File: interface.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "interface.h"

Interface::Interface(menu_model* model)
    : _model(model), OPTION_COUNT(_model->size()), _options(NULL) {}

Interface::~Interface()
{
    if (_options)
    {
        for (unsigned i = 0; i < OPTION_COUNT; ++i)
        {
            delete _options[i];
            _options[i] = NULL;
        }
    }

    delete [] _options;
    _options = NULL;
    
}

void Interface::build()
{
    // TODO this is unnesscary
    if (_model)
    {
        _model->build(_options);
    }
    return;
}

void Interface::display_menu() const
{
    std::cout << "=========================================================\n";
    int count = 1;
    for (unsigned i = 0; i < OPTION_COUNT; ++i)
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
    if (--index == OPTION_COUNT)
    {
        _exit.action();
        return;
    }

    // TODO The OR condition shouldn't be necessary, investigate further
    if (index > OPTION_COUNT || index < 0)
    {
        // TODO throw exception
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

void Interface::reset_input_stream()
{
    // reset failed state
    std::cin.clear();

    // discard characters up to the limit of the stream OR to newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}
