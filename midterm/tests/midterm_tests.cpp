/*
File: Midterm_tests.cpp

Description: Exercises for midterm prep

*/

#include "catch.hpp"
#include "linked_list.h"

TEST_CASE("Constructing lists")
{
    linked_list empty;

    int nums[] = { 1, 2, 3, 4, 5 };
    linked_list list(nums, nums + 5);

    REQUIRE(empty.empty());
    REQUIRE(empty.size() == 0);

    REQUIRE(list.size() == 5);
}

TEST_CASE("Copying lists")
{
    int nums[] = { 1, 2, 3, 4, 5, 6, 7 };
    linked_list origin(nums, nums + 5);

    linked_list copy(origin);

    linked_list copy2(nums, nums + 2);
    linked_list copy3(nums, nums + 7);

    copy2.copy(origin);
    copy3.copy(origin);

    REQUIRE(origin == copy);
    REQUIRE(origin == copy2);
    REQUIRE(origin == copy3);
}

TEST_CASE("Delete last")
{
    int nums[] = { 1, 2, 3, 4, 5, 6, 7 };

    linked_list first(nums, nums + 7);

    linked_list second(nums, nums + 6);

    REQUIRE(first.delete_last());

    first.display();
    second.display();
    REQUIRE(first == second);
}

TEST_CASE("pop front")
{
    int nums[] = { 1, 2, 3, 4, 5, 6, 7 };

    linked_list first(nums, nums + 7);

    linked_list second(nums+1, nums+7);

    REQUIRE(first.pop_front());

    REQUIRE(first == second);

}

TEST_CASE("Remove last two")
{
    int nums[] = { 1, 2, 3, 4, 5, 6, 7 };

    linked_list one_item(nums, nums + 1);

    linked_list no_items;

    linked_list multiple_items(nums,  nums + 7);
    linked_list two_items(nums, nums + 2);

    REQUIRE(!one_item.remove_last_two());
    REQUIRE(!no_items.remove_last_two());
    REQUIRE(multiple_items.remove_last_two());
    REQUIRE(two_items.remove_last_two());

    multiple_items.display();
}

TEST_CASE("Count negative")
{
    int nums[] = { 1, -2, 3, 4, -5, -6 };
    linked_list list(nums, nums + 6);

    REQUIRE(list.count_negative() == 3);
}
