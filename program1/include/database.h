/*
File: database.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef DATABASE_H
#define DATABASE_H

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

      // Adds a category to a database
      bool add_category(const char* name);

      // Removes the first category matching the name
      bool remove_category(const char* name);

      // Displays each category to the console
      void display_categories();

      // Add a project to a specified category
      bool add_project(const char* name, const Project& project);

      // Removes a project from a specified category
      bool remove_project(const char* category, const char* project);

      // Displays all projects in a specified category
      bool display_projects(const char* category);

      // Returns the number of categories in the database
      size_type size() const;

      // Returns true if the database is empty;
      bool empty();

  private:

      Categories _categories;

      struct remove_functor
      {
          const char* target;

          bool operator()(const Category& category)
          {
              return category.name() == target;
          }
      };

      // Returns read/write iterator to the category matching the name parameter
      Categories::iterator find_category(const char* name);
};

#endif // DATABASE_H


