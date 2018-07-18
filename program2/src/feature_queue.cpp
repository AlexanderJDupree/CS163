/*
 *
file: queue.h

brief:

author: alexander dupree

class: cs163

assignment: program2

date: 07/08/2018
*/

#include "feature_queue.h"

Feature_Queue::Feature_Queue()
    : features(queue()) {}

SString& Feature_Queue::dequeue(string& out_param)
{
    return features.pop_front(out_param);
}

Feature_Queue& Feature_Queue::enqueue(const string& data)
{
    features.push_back(data);
    return *this;
}

const SString& Feature_Queue::front() const
{
    return features.front();
}

const SString& Feature_Queue::back() const
{
    return features.back();
}

bool Feature_Queue::empty() const
{
    return features.empty();
}
