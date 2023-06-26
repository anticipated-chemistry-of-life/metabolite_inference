//
// Created by Marco Visani on 26.06.23.
//

#ifndef METABOLITE_INFERENCE_TREE_H
#define METABOLITE_INFERENCE_TREE_H
#include <unordered_map>
#include <vector>

class Node {
public:
	int id;
	Node *parent;
	std::vector<Node *> children;
	float branch_length_to_parent;

	Node(int id, float branch_length_to_parent, Node *parent = nullptr);

	bool is_leaf();
};

class Tree {
private:
	std::unordered_map<int, Node *> nodes;

public:
	~Tree();

	Node *add_node(int id, float branch_length_to_parent, int parent_id = -1);

	Node *get_node(int id);
};

#endif // METABOLITE_INFERENCE_TREE_H
