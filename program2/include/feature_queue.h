/*
File: queue.h

Brief:

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

    Feature_Queue();

    template <class InputIterator>
    Feature_Queue(InputIterator begin, InputIterator end);

    SString& dequeue(string& out_param);

    self_type& enqueue(const SString& data);

    const string& front() const;

    const string& back() const;

    bool empty() const;

  private:

    queue features;

};

template <class InputIterator>
Feature_Queue::Feature_Queue(InputIterator begin, InputIterator end)
    : features(begin, end) {}

#endif // QUEUE_H
