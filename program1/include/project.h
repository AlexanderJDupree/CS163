/*
File: project.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <map>
#include "sstring.h"

class Project
{
  public:
    typedef Project                    self_type;
    typedef SString                    string;
    typedef std::map<string, string>   Attributes;

    Project();

    Project(const Attributes& args);

    Project(const Project& project);

    ~Project();

    const string& name() const;

    friend std::ostream& operator << (std::ostream& os, const self_type& project);

    bool operator == (const Project& rhs) const;
    bool operator != (const Project& rhs) const;
    bool operator < (const Project& rhs) const;
    bool operator > (const Project& rhs) const;

    bool operator = (const Project& rhs);

  private:

    Attributes _attributes;
   
    string _name;
};

#endif // PROJECT_H