/*
File: rc_manager_tests.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#include <iostream>
#include "catch.hpp"
#include "rc_manager.h"

// Tests fixure is used when _data member is required for testing
struct rc_test_fixture : public reference_manager<char>
{
    rc_test_fixture(unsigned size=0) : reference_manager(size) 
    {
        ++REFERENCES;
    }

    rc_test_fixture(const rc_test_fixture& origin) : reference_manager(origin)
    {
        ++REFERENCES;
    }

    ~rc_test_fixture()
    {
        --REFERENCES;
    }

    char*& data() { return _data; }

    unsigned*& size_address() { return _size; }

    unsigned*& ref_count_address() { return _ref_count; }

    void initialize_array(char character)
    {
        for (unsigned i = 0; i < *_size; ++i)
        {
            _data[i] = character;
        }
        _data[*_size] = '\0';
    }

    static unsigned REFERENCES;
};

unsigned rc_test_fixture::REFERENCES = 0;

TEST_CASE("Constructing reference managers", "[rc_manager], [constructors]")
{
    SECTION("Default construction")
    {
        rc_test_fixture ref_counter;

        REQUIRE(ref_counter.ref_count() == 1);
        REQUIRE(ref_counter.size() == 0);

    }
    SECTION("Array construction")
    {
        rc_test_fixture ref_counter(10);

        ref_counter.initialize_array('a');

        REQUIRE(ref_counter.size() == 10);
        for(unsigned i = 0; i < 10; ++i)
        {
            CHECK(ref_counter.data()[i] == 'a');
        }
    }
    SECTION("Copy construction increases reference count")
    {
        rc_test_fixture origin(10);
        origin.initialize_array('a');

        rc_test_fixture copy(origin);
        rc_test_fixture double_copy(copy);

        REQUIRE(origin.ref_count() == 3);
        REQUIRE(copy.ref_count() == 3);
        REQUIRE(double_copy.ref_count() == 3);

        REQUIRE(origin.size() == 10);
        REQUIRE(copy.size() == 10);
        REQUIRE(double_copy.size() == 10);

        REQUIRE(origin.data() == copy.data());
        REQUIRE(copy.data() == double_copy.data());
    }
}

TEST_CASE("Deleting reference_manager's", "[rc_manager], [destructors]")
{
    SECTION("A unique reference_manager")
    {
        rc_test_fixture* fixture = new rc_test_fixture;

        delete fixture;

        REQUIRE(rc_test_fixture::REFERENCES == 0);
    }
    SECTION("Deleting a shared reference does not delete data")
    {
        rc_test_fixture* first = new rc_test_fixture(10);
        first->initialize_array('a');

        rc_test_fixture* second = new rc_test_fixture(*first); 
        rc_test_fixture* third = new rc_test_fixture(*second); 

        delete first;

        REQUIRE(second->data() == third->data());
        REQUIRE(second->ref_count() == 2);
        REQUIRE(third->size() == 10);

        delete second;
        delete third;
    }
    SECTION("Deleting all references releases data")
    {
        rc_test_fixture* first = new rc_test_fixture(10);
        first->initialize_array('a');

        rc_test_fixture* second = new rc_test_fixture(*first); 
        rc_test_fixture* third = new rc_test_fixture(*second); 

        delete first;
        delete second;
        delete third;

        // I couldn't figure out a way to mock that pointers to the data and 
        // dereference them to ensure the data was freed. Use valgrind to run
        // this test.
        
        REQUIRE(rc_test_fixture::REFERENCES == 0);
    }
}
