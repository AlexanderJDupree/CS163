/*
File: interface.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include "interface.h"

Interface::Interface(Menu& options) : options(options) {}

void Interface::build_menu(Menu& options)
{
    this->options = options;
}

void Interface::display_menu()
{
    std::cout << "============================================================\n";
    int count = 1;
    for (Menu::iterator it = options.begin(); it != options.end(); ++it)
    {
        std::cout << "\n  " << count++ << ".\t" << (*it)->option() << std::endl;
    }
    std::cout << "\n============================================================\n";
}
