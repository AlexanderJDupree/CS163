/*
File: linked_list.h

Description: Category ADT is a wrapper class for data structure. Category 
             manages the addition, removal, and inspection of Project objects.

             A Category is identified and compared against its name attribute.
             The name attribute makes use of a CUSTOM string class (SString) to
             handle the allocation, deallocation, and modification of 
             char pointers. This frees up the Category to manage only the 
             Projects container.

Author: Alexander DuPree

Date: 07/11/2018
*/

#ifndef CATEGORY_H
#define CATEGORY_H

#include "linked_list.h"
#include "project.h"


class Category
{
  public:
    typedef SString                     string;
    typedef Category                    self_type;
    typedef linear_linked_list<Project> Projects;
    typedef Projects::const_iterator    const_iterator;
    typedef Projects::size_type         size_type;

    // Calls Projects and Strings default constructor
    Category();

    // Calls projects default constructor, initialzes name member
    Category(const string& name);

    // Copy constructor
    Category(const Category& origin);

    // Default constructor is used as the string and Projects structures handle
    // their destruction.
    ~Category() {}

    // Returns the name of this category
    const string& name() const;

    // Adds a project to its collection, returns true if the addition was 
    // successfull
    bool add_project(const Project& project);

    // Removes the first project matching the name target
    bool remove_project(const string& name);

    // Displays each project in its collection to the console
    void display_projects();

    // Returns an iterator to the project matching the name argument
    const_iterator find_project(const string& name);

    // Returns an iterator to the first project in the category
    const_iterator begin() const;

    // Returns an iterator to one past the last project in the category
    const_iterator end() const;

    // Returns the number of projects currently in the category
    size_type size() const;

    // Comparison operators use the name member as the comparator
    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;
    bool operator < (const self_type& rhs) const;
    bool operator > (const self_type& rhs) const;

    // Prints the category to the console
    friend std::ostream& operator << (std::ostream& os, const Category& category);

  private:

    string _name; // The name of this category

    Projects _projects; // The projects belonging to this category

    // Predicate fullfilling functor object that compares name strings
    struct remove_functor
    {
        const string& target;

        bool operator()(const Project& project)
        {
            return project.name() == target;
        }
    };
};

#endif // CATEGORY_H
