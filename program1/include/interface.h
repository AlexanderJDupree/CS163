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

class menu_item
{
  public:
    virtual ~menu_item() {}
    virtual const char* option() const = 0;
    virtual void action() = 0;
};

class Interface
{
  public:
    typedef menu_item** menu;

    Interface(menu options, unsigned size);

    void display_menu();

    void run_action(unsigned index);

    static unsigned get_input(const char* prompt);


  private:

    menu _options;

    unsigned _size;

    static void reset_input_stream();
};

#endif // INTERFACE_H
