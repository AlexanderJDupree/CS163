/*
File: linked_list.h

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <cstddef>
#include <vector>

struct pair 
{
    typedef const char* string;
    
    string key;
    string value;
};

class Project
{
  public:
    typedef const char *      string;
    typedef std::vector<pair> Attributes;


    Project();

    Project(const Project& project);

    ~Project();

  private:
    
    Attributes attributes;
   
};

#endif // PROJECT_H