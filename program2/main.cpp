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
    wishlist_menu_model wishlist;
    shopping_menu_model shopping(wishlist.get_wishlist());

    // Phase 1: Queue Desired Features onto the wishlist
    Interface UI(&wishlist);

    UI.run();

    // Phase 2: Evaluate Products against the wishlist
    UI.build(&shopping);

    UI.run();

    // Phase 3: Summary

    return 0;
}

