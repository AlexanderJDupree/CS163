/*
file: main.cpp

brief:

author: alexander dupree

class: cs163

assignment: program2

date: 07/08/2018
*/

#include "wishlist_menu.cpp"
#include "shopping_menu.cpp"

int main()
{
    wishlist_menu_model model;

    Interface UI(&model);

    UI.run();

    return 0;
}

