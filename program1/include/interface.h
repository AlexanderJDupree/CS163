/*
File: interface.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include "sstring.h"

class menu_item
{
  public:
    virtual ~menu_item() {}
    virtual const SString option() const = 0;
    virtual void action() = 0;
};

class Interface
{
  public:

    typedef std::vector<menu_item*> Menu;

    Interface();

    Interface(Menu& options);

    void build_menu(Menu& options);

    void display_menu();

  private:

    Menu options;

};

#endif // INTERFACE_H
