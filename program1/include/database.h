/*
File: database.h

Description: Database ADT acts as a wrapper class for a container data structure
             Database manages the addition, removal, and inspection of Category
             member objects. Database also communicates with Categories to 
             request the addition, removal, and inspection of Project objects.

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <stdexcept>
#include "linked_list.h" 
#include "category.h"

class Database
{
  public:
      typedef SString                      string;
      typedef linear_linked_list<Category> Categories;
      typedef Categories::size_type        size_type;

      // Calls Categories default constructor
      Database();

      // Adds a category to a database, true if addition was successfull
      bool add_category(const string& name);

      // Removes the first category matching the name, true if removal success
      bool remove_category(const string& name);

      // Displays each category to the console
      void display_categories() const;

      // Add a project to a specified category, throws database_error if
      // project is a duplicate
      void add_project(const string& name, const Project& project);

      // Removes a project from a specified category, throws database_error
      // if project is not found
      void remove_project(const string& category, const string& project);

      // Displays all projects in a specified category
      void display_projects(const string& category);

      // Returns the number of categories in the database
      size_type size() const;

      // Returns true if the database is empty;
      bool empty();

  private:

      Categories _categories; // a container of category objects

      struct remove_functor
      {
          const string& target;

          bool operator()(const Category& category)
          {
              return category.name() == target;
          }
      };

      // Returns read/write iterator to the category matching the name parameter
      // throws if category not found
      Categories::iterator find_category(const string& name);
};

// database_error is the generic error type for the database.
struct database_error : public std::exception
{
    const char* error;

    database_error(const char* err = "database error")
        : error(err) {}

    const char* what() const throw()
    {
        return error;
    }
};

#endif // DATABASE_H


