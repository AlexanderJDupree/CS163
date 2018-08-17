# Program #5 Review
### _Written by Alexander DuPree_

## Data Structure Performance
Program #5 utilized an adjacency list to implement a Graph data structure. This Graph was used to represent a network of cities. The goal of this program was to assist in planning a possible path for a roadtrip. The user was able to plan a roadtrip from the existing graph of cities and receive a possible path to take for this roadtrip. The user could also add cities (vertices) onto the graph as well as connect roads (edges) to each city. The Graph was able to add these cities and connect the vertices with no issue. The benefits of the adjacency list, as opposed to an adjacency matrix, was that it used much less memory and was able to grow dynamically. 

## Data Structure Recommendation

This implementation of an adjacency list required we use an array of linked lists. These data structures had significant drawbacks however. Firstly, if we needed to add an edge we would first have to find the start and end vertice in the vertex array. This was a O(n) operation as we had to examine the entire array to ensure the vertex did exist. The same linear operation occured when searching through a vertice's adjacency list. If we implemented the the graph with hash tables or balanced trees we could achieve O(1) or O(log(n)) time for search operations. 

## Design

As far as application design, I feel that the data structures were sufficiently abstracted. A client using the application would have  difficulty determining exactly which data structures were being used. The main, and other classes had no knowledge of the specifics of the Table ADT's implementation. Instead, they relied on a public interface to accomplish the goals of the program. I was also able to abstract the depth first search algorithm to be agnostic of the action being performed on each vertex in the path. This allowed me to pass in functions to perform specific actions like count, display, or remove. 

## Inefficiences and Feature Additions

The greatest inefficiencies were those dealing with the data structures chosen for the adjacency list. Those inefficiencies have been already discussed. As far as feature additions I would have like to further abstract the Graph class to allow it to be instantiated with different traits. For example, give the user the ability to instantiate the graph as a directional graph or a undirected weighted graph, or any combination thereof. It would also be a entertaining challenge to implement the different search algorithms like breadth first search, djikstra, or A-Star. 
