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

    template <typename T>
    static T& get_input(const char* prompt, T& out_param);


  private:

    menu _options;

    unsigned _size;

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
