//
// Created by Marco Visani on 26.06.23.
//

#include "TTree.h"
#include <stdexcept>

Node::Node(int id, float branch_length_to_parent, Node *parent)
    : id(id), branch_length_to_parent(branch_length_to_parent), parent(parent) {}

bool Node::is_leaf() { return children.empty(); }

Tree::~Tree() {
	for (auto pair : nodes) { delete pair.second; }
}

Node *Tree::add_node(int id, float branch_length_to_parent, int parent_id) {
	Node *parent = nullptr;
	if (parent_id != -1) {
		auto parent_it = nodes.find(parent_id);
		if (parent_it == nodes.end()) { throw std::runtime_error("Parent id not found"); }
		parent = parent_it->second;
	}

	Node *node = new Node(id, branch_length_to_parent, parent);
	if (parent) { parent->children.push_back(node); }
	nodes[id] = node;
	return node;
}

Node *Tree::get_node(int id) {
	auto it = nodes.find(id);
	if (it == nodes.end()) { throw std::runtime_error("Node id not found"); }
	return it->second;
}
