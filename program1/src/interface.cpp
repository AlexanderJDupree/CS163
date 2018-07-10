/*
File: interface.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "interface.h"

Interface::Interface(menu options, unsigned size)
    : _options(options), _size(size) {}

void Interface::display_menu()
{
    std::cout << "=========================================================\n";
    int count = 1;
    for (unsigned i = 0; i < _size; ++i)
    {
        std::cout << "\n  " << count++ << ".\t" 
                  << _options[i]->option() << std::endl;
    }
    std::cout << "\n=========================================================\n";
    return;
}

unsigned Interface::get_input(const char* prompt)
{
    unsigned input = 0;

    std::cout << prompt;
    std::cin >> input;

    if (std::cin.fail())
    {
        reset_input_stream();
    }

    return input;
}

void Interface::run_action(unsigned index)
{
    if (index >= _size || index < 0)
    {
        // TODO throw exception
        return;
    }

    _options[index]->action();
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
