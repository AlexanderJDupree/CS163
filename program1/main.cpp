/*
File: main.cpp

Description:

Author: Alexander DuPree

Date: 06/27/2018
*/

#include <iostream>
#include "database_model.h"

struct database_builder : public model_factory
{
    menu_model* build_model()
    {
        return new database_model;
    }
};

int main()
{
    database_builder factory;

    Interface UI(&factory);

    UI.build();

    UI.run();

    return 0;
}

