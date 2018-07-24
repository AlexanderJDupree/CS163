/*
File: queue.h

Brief: Feature Queue is the implementation of a Queue ADT utilizing the 
       circular_linked_list as the underlying data structure. The Feature queue
       stores desired "Features" of a computer as a SString. SString(Shared 
       string) is an immutable reference counted string class I wrote. This 
       allows us to store these features without incuring a copy cost for the 
       feature strings.

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/08/2018
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "circular_list.h"
#include "sstring.h"

class Feature_Queue
{
  public:

    typedef SString                      string;
    typedef Feature_Queue                self_type;
    typedef circular_linked_list<string> queue;

    /****** CONSTRUCTORS ******/

    Feature_Queue();

    template <class InputIterator>
    Feature_Queue(InputIterator begin, InputIterator end);

    // The default destructor is used as the underlying circular_linked_list
    // class will handle the deallocation of resources

    /****** MODIFIERS ******/

    SString& dequeue(string& out_param);

    self_type& enqueue(const SString& data);

    bool clear_queue();

    /****** ELEMENT ACCESS ******/

    const string& front() const;

    const string& back() const;

    void display() const;

    /****** CAPACITY ******/

    bool empty() const;

    unsigned size() const;

  private:

    queue features; // Stores each feature enqueued
};

template <class InputIterator>
Feature_Queue::Feature_Queue(InputIterator begin, InputIterator end)
    : features(begin, end) {}

#endif // QUEUE_H
