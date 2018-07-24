/*
File: interface.h

Description: 

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef MENU_OBJECTS_H
#define MENU_OBJECTS_H

#include <iostream>
#include <stdexcept>

// Abstract base class for all menu options in the interface
class menu_item
{
  public:
    virtual ~menu_item() {}
    
    // Returns the menu option caption
    virtual const char* option() const = 0;

    // Executes the action mapped to the option
    virtual void action() = 0;
};

// Specialization of the menu_item, required for menus to have an exit condition
class exit_item : public menu_item
{
  public:

    exit_item() : exit(false) {}

    virtual bool operator()() = 0;

  protected:

    bool exit;
};

// The model is used to build and connect all menu_items into the interface
class menu_model
{ 
  public:

    menu_model()
        : _options(NULL), _exit(NULL) {}

    // Returns the number of options in the menu
    virtual unsigned size() const = 0;

    // Returns the option mapped to the specific index
    virtual menu_item* option(unsigned index) = 0;

  protected:

    // The model interface does not handle any deallocation, ensure memory is 
    // freed correctly with the concrete implementations
    virtual ~menu_model() {}

    // Builds the menu_items and connect their dependencies
    virtual void build() = 0;

    // Checkst the exit condition, returns the status
    virtual bool exit() = 0;

    menu_item** _options; // An array of menu_item pointers represents the menu

    exit_item* _exit; // The exit condition structure

    friend class Interface;
};

class model_viewer 
{
  public:

    virtual ~model_viewer() {}

    virtual void draw(menu_model* model) const = 0;
};


// Default exit item
class default_exit : public exit_item
{
  public:

    default_exit() : exit_item() {}

    const char* option() const { return "Exit Application"; }

    void action() { exit = true; }

    bool operator()() { return exit; }
};

class basic_model : public menu_model
{   
  public:

    basic_model() : menu_model() {}
    
    virtual ~basic_model()
    {
        clear_menu();
    }

  protected:

    virtual void clear_menu()
    {
        if (!_options)
        {
            return; 
        }

        for (unsigned i = 0; i < size(); ++i)
        {
            delete _options[i];
            _options[i] = NULL;
        }

        delete [] _options;

        _options = NULL;
        return;
    }

    unsigned size() const { return SIZE; }

    void build()
    {
        if (_options)
        {
            clear_menu();
        }

        _options = new menu_item*[SIZE];
        _exit = new default_exit;

        _options[0] = _exit;
        return;
    }

    bool exit()
    {
        return (*_exit)();
    }

    menu_item* option(unsigned index)
    {
        if(index >= size())
        {
            throw std::out_of_range("Index out of bounds, no menu_item");
        }

        return _options[index];
    }

    static const int SIZE = 1;
};


class basic_view : public model_viewer
{
  public:

    void draw(menu_model* model) const
    {
        std::cout << "=========================================================\n";
        int count = 1;
        for (unsigned i = 0; i < model->size(); ++i)
        {
            std::cout << "\n  " << count++ << ".\t" 
                      << model->option(i)->option() << std::endl;
        }
        std::cout << "\n=========================================================\n";
        return;
    }
};

#endif // MENU_OBJECTS_H
