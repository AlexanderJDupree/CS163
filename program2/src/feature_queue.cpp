/*
file: queue.cpp

brief:  Implementation file for the Feature_Queue class

author: Alexander DuPree

class: CS163

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

bool Feature_Queue::clear_queue()
{
    if(empty())
    {
        return false;
    }

    return features.clear().empty();
}

const SString& Feature_Queue::front() const
{
    return features.front();
}

const SString& Feature_Queue::back() const
{
    return features.back();
}

void Feature_Queue::display() const
{
    std::cout << "    FEATURE WISHLIST\n===================================\n";

    if (features.empty())
    {
        std::cout << "Your wishlist is empty\n";
        return;
    }
    
    queue::const_iterator it = features.begin();
    do {
        std::cout << *it << std::endl;
        ++it;
    } while (it != features.end());
    std::cout << "===================================\n";
    return;
}

bool Feature_Queue::empty() const
{
    return features.empty();
}

unsigned Feature_Queue::size() const
{
    return features.size();
}

