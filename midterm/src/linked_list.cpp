
#include "linked_list.h"

linked_list::linked_list()
    : head(NULL), tail(NULL) {}

linked_list::~linked_list()
{

}

void linked_list::push_front(const int& data)
{
    node* temp = new node;
    temp->data = data;
    temp->next = head;
    head = temp;

    if(tail == NULL)
    {
        tail = head;
    }

    return;
}

void linked_list::push_back(const int& data)
{
    if(!head)
    {
        push_front(data);
    }

    node* temp = new node;
    temp->data = data;
    temp->next = NULL;
    tail->next = temp;
    tail = temp;
    
    return;
}
