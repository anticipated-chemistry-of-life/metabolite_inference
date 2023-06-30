//
// Created by Marco Visani on 26.06.23.
//

#ifndef METABOLITE_INFERENCE_TREE_H
#define METABOLITE_INFERENCE_TREE_H
#include <string>
#include <unordered_map>
#include <vector>

// Function to split a string into a vector of substrings, separated by a delimiter
std::vector<std::string> split(const std::string &s, char delimiter);

class Node {
public:
	int id;                        // unique identifier for the node
	Node *parent;                  // pointer to parent node
	std::vector<Node *> children;  // vector of pointers to child nodes
	float branch_length_to_parent; // branch length to parent node

	// Constructor, initializes a Node with id, branch_length_to_parent and parent node
	Node(int id, float branch_length_to_parent, Node *parent = nullptr);

	// Method to check if the node is a leaf (has no children)
	bool is_leaf();
};

class Tree {
private:
	std::unordered_map<int, Node *> nodes; // a map to store nodes with their ids

public:
	// Destructor, deletes all nodes
	~Tree();

	// Add a node to the tree
	Node *add_node(int id, float branch_length_to_parent, int parent_id = -1);

	// Get node by its id
	Node *get_node(int id);

	// Method to load the tree from a file
	void load_from_file(const std::string &filename, char separator);
};

#endif // METABOLITE_INFERENCE_TREE_H
