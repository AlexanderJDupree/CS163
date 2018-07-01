/*
File: project.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <cstddef>
#include <vector>
#include "sstring.h"

struct pair
{
    typedef SString string;

    pair(string key, string value) : key(key), value(value) {}

    bool operator == (const pair& rhs) const
    {
      return key == rhs.key && value == rhs.value;
    }
    bool operator < (const pair& rhs) const
    {
      return key == rhs.key && value < rhs.value;
    }
    
    string key;
    string value;
};

class Project
{
  public:
    typedef Project                    self_type;
    typedef SString                    string;
    typedef pair                       field;
    typedef std::vector<field>         Attributes;
    typedef Attributes::iterator       iterator;
    typedef Attributes::const_iterator const_iterator;

    Project();

    Project(Attributes args);

    Project(const Project& project);

    ~Project();

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // get attribute
    // get all attributes

    friend std::ostream& operator << (std::ostream& os, const self_type& project);

    bool operator == (const Project& rhs) const;
    bool operator != (const Project& rhs) const;
    bool operator < (const Project& rhs) const;
    bool operator > (const Project& rhs) const;

    bool operator = (const Project& rhs);
    

  private:
    
    Attributes attributes;
   
};

#endif // PROJECT_H