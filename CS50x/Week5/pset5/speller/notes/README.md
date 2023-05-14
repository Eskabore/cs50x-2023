Dictionary

This is a C implementation of a dictionary that uses a hash table to store words and efficiently check if a given word is in the dictionary. It includes the following functions:

`bool check(const char *word)`: This function takes a word as input and returns a boolean indicating whether it is in the dictionary or not. It is case-insensitive, meaning that it will return true for any capitalization of the word.

`unsigned int hash(const char *word)`: This function takes a word as input and returns an unsigned integer that represents the hash value of the word. The hash value is calculated by summing the ASCII values of each character in the word and taking the modulo of the result with the number of buckets in the hash table.

`bool load(const char *dictionary)`: This function loads the dictionary into memory by reading the words from the dictionary file and inserting them into the hash table. It returns true if the dictionary was successfully loaded, or false if there was an error (e.g., if the file could not be opened or if there was not enough memory to allocate for a new word).

`unsigned int size(void)`: This function returns the number of words in the dictionary. It counts the number of words in each bucket of the hash table by traversing the linked list at each index and incrementing a count for each node encountered.

`bool unload(void)`: This function unloads the dictionary from memory by freeing the memory allocated for each word in the hash table. It returns true if the dictionary was successfully unloaded, or false if there was an error (e.g., if a node in the hash table could not be freed).
The hash table is an array of linked lists, with each element of the array representing a bucket. Each bucket contains a linked list of nodes, where each node represents a word in the dictionary. The linked list is implemented using pointers, with each node containing a word and a pointer to the next node.

The check() and load() functions use the hash() function to calculate the index in the hash table where a word should be inserted or searched for. This allows the functions to access the correct bucket in the hash table and traverse the linked list at that index in constant time, making the overall time complexity of these functions O(1) on average.

The size() function has a time complexity of O(n), where n is the number of words in the dictionary, because it must traverse the entire hash table and count the number of nodes in each bucket.

The unload() function has a time complexity of O(n), where n is the number of words in the dictionary, because it must traverse the entire hash table and free the memory for each node.