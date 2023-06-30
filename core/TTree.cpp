//
// Created by Marco Visani on 26.06.23.
//

#include "TTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<std::string> split(const std::string &s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) { tokens.push_back(token); }
	return tokens;
}

// Node constructor implementation
Node::Node(int id, float branch_length_to_parent, Node *parent)
    : id(id), parent(parent), branch_length_to_parent(branch_length_to_parent) {}

// Node is_leaf method implementation
bool Node::is_leaf() {
	// A node is a leaf if its children vector is empty
	return children.empty();
}

// Tree destructor implementation
Tree::~Tree() {
	// Iterate through the nodes map and delete each Node object
	for (auto pair : nodes) { delete pair.second; }
}

// Tree add_node method implementation
Node *Tree::add_node(int id, float branch_length_to_parent, int parent_id) {
	Node *parent = nullptr;

	// If the parent_id is not -1, we find the parent node in the nodes map
	if (parent_id != -1) {
		auto parent_it = nodes.find(parent_id);
		if (parent_it == nodes.end()) { throw std::runtime_error("Parent id not found"); }
		parent = parent_it->second;
	}

	// Create a new Node object and add it to the nodes map
	Node *node = new Node(id, branch_length_to_parent, parent);
	if (parent) {
		// If the parent exists, add the newly created node to its children vector
		parent->children.push_back(node);
	}
	nodes[id] = node;
	return node;
}

// Get node from a tree
Node *Tree::get_node(int id) {
	// Find the Node object in the nodes map by its id
	auto it = nodes.find(id);
	if (it == nodes.end()) { throw std::runtime_error("Node id not found"); }
	return it->second;
}

void Tree::load_from_file(const std::string &filename, char separator) {
	std::ifstream file(filename);
	if (!file.is_open()) { throw std::runtime_error("Cannot open file"); }

	std::string line;
	while (std::getline(file, line)) {
		auto tokens = split(line, separator);
		if (tokens.size() != 3) {
			std::cerr << "Invalid line: " << line << std::endl;
			continue;
		}

		int id                        = std::stoi(tokens[0]);
		int parent_id                 = std::stoi(tokens[1]);
		float branch_length_to_parent = std::stof(tokens[2]);

		add_node(id, branch_length_to_parent, parent_id);
	}
}