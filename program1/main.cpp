/*
File: main.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include "menu_options.h"


int main()
{
    database_model database;

    Interface UI(&database);

    UI.build();

    UI.run();

    return 0;
}

