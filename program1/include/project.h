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

    typedef Project self_type;
    typedef SString string;

    Project();

    Project(const string attributes[]);

    Project(const Project& project);

    ~Project();

    const string& name() const;

    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;
    bool operator < (const self_type& rhs) const;
    bool operator > (const self_type& rhs) const;

    // TODO
    bool operator = (const Project& rhs);

    friend std::ostream& operator << (std::ostream& os, const Project& project);

  private:

    string _name;
    string _due_date;
    string _due_time;
    string _late_date;
    string _data_structure;

};

#endif // PROJECT_H
