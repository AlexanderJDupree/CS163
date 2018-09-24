/*
File: menu.h

Description: menu.h provides the abstract base classes for use in the Interface
             class. These abstract interfaces can be specialized for whichever
             use necessary however, this file contains basic implementations for
             the menu_item, model, and viewer classes. It is recommended to 
             follow the format of these basic classes when specializing your own
             items, models, or viewers. 

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 07/11/2018
*/

#ifndef MENU_OBJECTS_H
#define MENU_OBJECTS_H

#include <iostream> // std::cout, std::cin, std::endl;
#include <stdexcept> // std::out_of_range

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

    // Returns the option mapped to the specific index, throws std::out_of_range
    // if the indexs is not valid
    virtual menu_item* option(unsigned index) = 0;

  protected:

    // The model interface does not handle any deallocation, ensure memory is 
    // freed correctly with the concrete implementations
    virtual ~menu_model() {}

    // Builds the menu_items and connect their dependencies
    virtual void build() = 0;

    // Checks the exit condition, returns the status
    virtual bool exit() = 0;

    menu_item** _options; // An array of menu_item pointers represents the menu

    exit_item* _exit; // The exit condition structure

    friend class Interface;
};

// The abstract interface for the viewer, the views responsibility is to render
// the models menu implementation onto the console
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

// Basic_model is a default menu_model implementation. When specializing models
// it is recommended to inherit from the basic_model, as it has working 
// implementations for deallocation and exit and option methods. If basic_model
// is inherited the only methods that need to defined are the destructor, size, 
// and build.
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


// basic viewer 
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
