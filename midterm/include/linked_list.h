/*
File: linked_list.h

Description: Playground for testing linear linked list operations to prepare for 
             CS163 midterm
*/


#ifndef LLL_H
#define LLL_H

#include <iostream>
#include <cstddef>

struct node
{
    int data;
    node* next;
};

class linked_list
{
  public:

    linked_list();

    template <class InputIterator>
    linked_list(InputIterator begin, InputIterator end);

    linked_list(const linked_list& origin);

    ~linked_list();

    void push_front(const int& data);
    void push_back(const int& data);
    bool pop_front();

    bool empty() const;

    unsigned size() const;

    bool copy(const linked_list& origin);

    bool operator==(const linked_list& rhs) const;

    void display() const;

    bool clear();

    bool delete_last();

    bool remove_last_two();

    unsigned count_negative() const;

  private:
    node* head;
    node* tail;

    unsigned size(node* current) const;
    bool copy(node*& src, node* origin);
    bool clear_list(node*& current);
    int delete_last(node*& current);
    int remove_last_two(node*& current);

    unsigned count_negative(node* current) const;

};

template <class InputIterator>
linked_list::linked_list(InputIterator begin, InputIterator end)
    : head(NULL), tail(NULL)
{
    for (; begin != end; ++begin)
    {
        push_back(*begin);
    }
}

#endif // LLL_H
