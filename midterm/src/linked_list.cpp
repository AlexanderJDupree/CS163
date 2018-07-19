
#include "linked_list.h"

linked_list::linked_list()
    : head(NULL), tail(NULL) {}

linked_list::linked_list(const linked_list& origin)
    : head(NULL), tail(NULL)
{
    copy(origin);
}

linked_list::~linked_list()
{
    clear_list(head);
}

bool linked_list::copy(const linked_list& origin)
{
    if (!origin.head)
    {
        return false;
    }

    return copy(head, origin.head);
}

bool linked_list::copy(node*& src, node* origin) 
{
    // Base case
    if (origin == NULL)
    {
        // Clear the rest of this list if it was longer than the copy
        return clear_list(src);
    }

    // List was empty, or shorter than the origin
    if (src == NULL)
    {
        src = new node;
        src->next = NULL;
    }

    tail = src; // Tail gets updated as we go
    src->data = origin->data;

    return copy(src->next, origin->next);

}

bool linked_list::clear()
{
    if (!head)
    {
        return false;
    }

    return clear_list(head);
}

bool linked_list::clear_list(node*& current)
{
    // Base case, reached end of list
    if(current == NULL)
    {
        return true;
    }

    // Hold onto next node
    node* next = current->next;

    // Delete the current node and set to null
    delete current;
    current = NULL;

    // Recursive call
    return clear_list(next);
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
        return;
    }

    node* temp = new node;
    temp->data = data;
    temp->next = NULL;
    tail->next = temp;
    tail = temp;
    
    return;
}

bool linked_list::pop_front()
{
    if (!head)
    {
        return false;
    }

    node* next = head->next;

    // Edge case, tail is head
    if(tail == head)
    {
        tail = next;
    }

    delete head;
    head = next;
    return true;
}

bool linked_list::empty() const
{
    return !(head);
}

unsigned linked_list::size() const
{
    if (!head)
    {
        return 0;
    }

    return size(head);
}

unsigned linked_list::size(node* current) const
{
    if (current == tail)
    {
        return 1;
    }

    return 1 + size(current->next);
}

bool linked_list::operator==(const linked_list& rhs) const
{
    if (size() != rhs.size())
    {
        return false;
    }

    node* left = head;
    node* right = rhs.head;
    while(left != NULL)
    {
        if (left->data != right->data)
        {
            return false;
        }
        left = left->next;
        right = right->next;
    }

    return true;
}

void linked_list::display() const
{
    node* temp = head;
    while(temp != NULL)
    {
        std::cout << "n: "<< temp->data << ' ';
        temp = temp->next;
    }
    std::cout << std::endl;
}

bool linked_list::delete_last()
{
    if(!head)
    {
        return false;
    }

    return delete_last(head);
}

int linked_list::delete_last(node*& current)
{
    // Base case
    if(current->next == NULL)
    {
        return 2;
    }

    if(delete_last(current->next) == 2)
    {
        tail = current;
        delete current->next;
        current->next = NULL;
        return 1;
    }

    return 1;
}

bool linked_list::remove_last_two()
{
    if(!head || !head->next)
    {
        return false;
    }

    return remove_last_two(head);
}

int linked_list::remove_last_two(node*& current)
{
    /*
    // Base case
    if(current->next == tail)
    {
        delete tail;
        delete current;
        current = NULL;
        return 2;
    }

    if(remove_last_two(current->next) == 2)
    {
        tail = current;
        return 1;
    }
    */
    
    if (current->next == NULL)
    {
        delete current;
        current = NULL;
        return 2;
    }

    int status = remove_last_two(current->next);
    if( status == 2)
    {
        delete current;
        current = NULL;
        return 3;
    }

    if(status == 3)
    {
        tail = current;
    }

    return 1;
}

unsigned linked_list::count_negative() const
{
    return count_negative(head);
}

unsigned linked_list::count_negative(node* current) const
{
    // Base Case
    if (!current)
    {
        return 0;
    }

    if(current->data < 0)
    {
        return 1 + count_negative(current->next);
    }

    return count_negative(current->next);
}
