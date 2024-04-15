## Implementation Documentation of Hash Table and Collision Handling

### Hash Table
A hash table is a data structure that allows for efficient storage and retrieval of data. It works by associating keys with values, allowing access to a specific value through its key in constant time, ideally. This is possible thanks to a hash function, which transforms the key into an index in the table.

### Collision Handling
Collision occurs when two different keys are mapped to the same index in the hash table. There are different approaches to dealing with this problem:

* Separate Chaining: In this approach, each cell of the hash table is a linked list of elements. When a collision occurs, elements with different keys but that map to the same index are stored in a list.

* Open Addressing: Here, when a collision occurs, another location in the table is sought to store the element. This can be done in different ways, such as linear probing, quadratic probing, or double hashing.

### Repository Objective
The objective of this repository is to document the implementation of a hash table and the different collision handling methods mentioned above. This includes the source code of the implementation in one or more programming languages, along with usage examples, detailed explanations, and, whenever possible, automated tests to ensure the correct functioning of the implementation.
