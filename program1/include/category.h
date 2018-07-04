/*
File: linked_list.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef CATEGORY_H
#define CATEGORY_H

#include <vector>
#include "linked_list.h"
#include "project.h"


class Category
{
  public:
    typedef SString                  string;
    typedef Category                 self_type;
    typedef Sorted_List<Project>     Projects;
    typedef std::vector<string>      Fields;
    typedef Projects::const_iterator const_iterator;
    typedef Projects::size_type      size_type;

    Category(const string& name, const Fields& fields);

    template <class InputIterator>
    Category(const string& name, InputIterator begin, InputIterator end)
        : _name(name), _fields(Fields(begin, end)), _projects(Projects()) {}

    Category(const Category& category);

    ~Category() {}

    const string& name();

    const Fields& fields();

    bool add_project(Fields attributes);

    const_iterator find_project(const string& name);

    const_iterator begin() const;
    const_iterator end() const;

    size_type size() const;

    bool operator == (const self_type& rhs);
    bool operator != (const self_type& rhs);
    bool operator < (const self_type& rhs);
    bool operator > (const self_type& rhs);

    bool operator = (const self_type& origin);

    static void swap(self_type& new_category, self_type& old_category);

  private:

    string _name; // The name of this category

    Fields _fields; // The valid field data for each project

    Projects _projects; // The projects belonging to this category

};

#endif // CATEGORY_H
