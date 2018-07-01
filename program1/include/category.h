/*
File: linked_list.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef CATEGORY_H
#define CATEGORY_H

#include "linked_list.h"
#include "project.h"

class Category
{
  public:
    typedef const char*          string;
    typedef Category             self_type;
    typedef Sorted_List<Project> Projects;

    Category();

    Category(const Category& category);

    ~Category();

    // Add a project
    // find a project
    // get a project

    bool operator != (const self_type& rhs);
    bool operator < (const self_type& rhs);
    bool operator > (const self_type& rhs);

    bool operator = (const self_type& origin);

    static void swap(self_type& new_category, self_type& old_category);

  private:

    string name; // The name of this category

    Projects projects; // The projects belonging to this category

};

#endif // CATEGORY_H