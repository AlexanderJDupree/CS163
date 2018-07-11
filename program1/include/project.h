/*
File: project.h

Description: Project ADT stores specific data related to it's category. Each
             project contains the following data

             1. Name
             2. Due date
             3. Late Data
             4. Due Time
             5. Data structure. 

             Each project  data member is immutable and can only be inspected 
             via the << operator. 

             The Project ADT makes use of a custom string class (SString) to 
             handle the dynamic allocation, deallocation, and comparison of
             const char pointers. 

             The Project is identified and compared against its name member.

Author: Alexander DuPree

Date: 07/11/2018
*/

#ifndef PROJECT_H
#define PROJECT_H

#include "sstring.h"

class Project
{
  public:

    typedef Project self_type;
    typedef SString string;

    // Instantiates an empty project
    Project();

    // Loops through the attributes array, copying the string to the correct 
    // fields
    Project(const string attributes[]);

    // Copies constructor
    Project(const Project& project);

    // Default destructor is used as the Project ADT does not manage any 
    // resources. All allocation and memory management is handled by the SString
    // class
    ~Project();

    // Returns the name of the project
    const string& name() const;

    // Comparison/equality operators use the name as the comparator
    bool operator == (const self_type& rhs) const;
    bool operator != (const self_type& rhs) const;
    bool operator < (const self_type& rhs) const;
    bool operator > (const self_type& rhs) const;

    // Prints the projects attributes to the console
    friend std::ostream& operator << (std::ostream& os, const Project& project);

  private:

    string _name;
    string _due_date;
    string _due_time;
    string _late_date;
    string _data_structure;

};

#endif // PROJECT_H
