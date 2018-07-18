/*
File: linked_list.h

Description: Playground for testing linear linked list operations to prepare for 
             CS163 midterm
*/


#ifndef LLL_H
#define LLL_H

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

    ~linked_list();

    void push_front(const int& data);
    void push_back(const int& data);

  private:
    node* head;
    node* tail;

};

template <class InputIterator>
linked_list(InputIterator begin, InputIterator end)
{

}

#endif // LLL_H
