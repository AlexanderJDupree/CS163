# Program #1 Design
>## Written by Alexander DuPree

## Task and Purpose
Program #1 focus is in the design, usage and implementation for manipulating a **linear linked list** (_LLL_) data structure to store and manage an **abstract data type** (_ADT_). As such we were tasked to perform the following:

- Create a _LLL_ that will store a unique set of *categories* (e.g., assignments, readings, labs)
- Each *category* contains a _LLL_ that stores a unique set of *projects*.
    - A *project* is an item of work belonging to a specific category (e.g., reading #1 belongs to readings *category*)
- The client should have the following functionality:
    1. Add a new *category* of work.
    2. Remove a *category* of work.
    3. Add a *project* within a *category*
    4. Remove a *project* from a *category*
    5. Display all *categories*
    6. Display all *projects* in a *cotegory*

## Design Considerations

One of the primary goals of this project is to create an _ADT_ that "hides" the implementation of our _LLL_ data structure. We must also design the _LLL_ and _ADT's_ to be "plugs" and "sockets". Meaning that our _ADT_ is dependent on a *container* but the exact structure of that container should be an abstract detail that has no effect on how our _ADT_ is implemented. 

As for as the client-side programmer, he/she should only have knowledge of how to use our _ADT_ to create a user-application. Our _ADT_ will perform as a 'black box', providing a basic public methods to add and/or retrieve data from our data structure. 

## Data Flow

With this design consideration in mind the data will flow like this:

![Imgur](https://i.imgur.com/wnjF8o2.png)

- The user will interact with the scheduler and _request_ to add/remove/display a *category* of work or add/remove/display a *project* within a *category*. 
- The scheduler will then validate, clean, and package the user's input into a format that our *database* will accept. 
- The database will then forward the request to the appropiate *category* (or create a *category*). 
- Once the request is received at the correct category, we will then search for the desired project and return a read only reference to it. 
- The Database wil forward this request to the schuduler unit.
- The scheduler will present the data and then wait for the next user request.

## Data Structures and Abstract Data Types

Given the scope of the assignment we are limited to the use of only one data structure, a **linear linked list**. However, we will be using multiple _ADT's_ to store data efficiently and to act as a wrapper for our _LLL_.

### *Sorted_List*
The *sorted list* will act as the primary worker for our program. The *sorted_list* is a **linear linked list** with only one public modifier: *add()*. This modifier will insert new data into the list in a **SORTED** position. Keeping the list in a sorted state will prevent us from having to sort it later, satisfying the requirement to keep the *categories* sorted alphabetically. 

One important feature of our *sorted_list* is that is templated. Because we are required to have a _LLL_ of *category* objects, who in turn would have a _LLL_ of *project* objects we are faced with two options:
1. Write our _LLL_ code to support a *project* _ADT_ and then duplicate that code; replacing any reference to a *project* _ADT_ with a *category* _ADT_. 

    or

2. write the code once as a template and be done with it. 

The other benefits of the D.R.Y principle apply as well. 

Our _LLL_ will require other functions to be manipulated successfully in our wrapper classes, below is a list of the public functions and their uses:

| Function | Summary |
|----------|---------|
|add | inserts **UNIQUE** data into a **sorted** postion in the list and returns true. If the data is **not** unique the function will return false. 
|begin | returns a **read only** iterator to the beginning of the list, if the list is empty then begin == end.
|end | returns an iterator to one past the end of the list, It is dangerous to dereference this iterator
|find | returns an iterator to the matching data, if there is no matching data the function returns an end iterator
|empty | returns true if the list is empty

### *Project*
The *Project* _ADT_ will act as a basic storage unit for each *project* that belongs in a specific *category*. Each project requires certain information for it to be complete.

1. Name of the project
2. On time due date.
3. Late due date.
4. due time. 
5. Data structure used. 

The *Project* _ADT_ will store this data in the form of null-terminated C-strings, and will handle the allocation/destruction of these strings. The *Project* _ADT_ will have a default and overloaded constructor as well as getters for each member. 

### *Category*
The *category* _ADT_ will act as a wrapper class for our *sorted_list* _LLL_ data structure. It will provide methods to add, remove, and inspect *Project* _ADT's_ stored in it's _LLL_.

Below is a list of the public functions the *database* will interact with. 