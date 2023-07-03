//
// Created by Marco Visani on 26.06.23.
//

#ifndef METABOLITE_INFERENCE_TREE_H
#define METABOLITE_INFERENCE_TREE_H
#include <set>
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
	[[nodiscard]] bool is_leaf() const;
};

class Tree {
private:
	std::unordered_map<int, Node *> nodes; // a map to store nodes with their ids
	int num_roots = 0;
	std::set<int> leaf_nodes;
	std::set<int> root_nodes;

public:
	// Destructor, deletes all nodes
	~Tree();

	// Add a node to the tree
	Node *add_node(int id, float branch_length_to_parent, int parent_id = -1);

	// Get node by its id
	Node *get_node(int id);

	// Method to load the tree from a file
	void load_from_file(const std::string &filename, char separator);

	// Find the number of roots in the tree
	[[nodiscard]] int count_roots() const { return num_roots; }

	// Method to get all the leaves of the tree
	[[nodiscard]] std::set<int> get_leaf_nodes() const { return leaf_nodes; }

	// Method to get all the root nodes
	[[nodiscard]] std::set<int> get_root_nodes() const { return root_nodes; }
};
#endif // METABOLITE_INFERENCE_TREE_H
