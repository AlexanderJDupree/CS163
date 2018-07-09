/*
File: project.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef PROJECT_H
#define PROJECT_H

#include "sstring.h"
#include "linked_list.h"

class Project
{
  public:
    typedef Project                    self_type;
    typedef SString                    string;
    typedef linear_linked_list<string> Attributes;

    Project();

    template <class InputIterator>
    Project(const string& identifier, InputIterator begin, InputIterator end)
      : _attributes(begin, end), _identifier(identifier) {}

    Project(const Project& project);

    ~Project();

    const string& identifier() const;


    bool operator == (const Project& rhs) const;
    bool operator != (const Project& rhs) const;
    bool operator < (const Project& rhs) const;
    bool operator > (const Project& rhs) const;

    // TODO
    bool operator = (const Project& rhs);

    friend std::ostream& operator << (std::ostream& os, const Project& project);

  private:

    Attributes _attributes;

    string _identifier;
};

#endif // PROJECT_H
