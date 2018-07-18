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

SString& Feature_Queue::dequeue(SString& out_param)
{
    return features.pop_front(out_param);
}

bool Feature_Queue::empty() const
{
    return features.empty();
}
