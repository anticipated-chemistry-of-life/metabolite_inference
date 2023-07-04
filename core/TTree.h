//
// Created by Marco Visani on 26.06.23.
//

#ifndef METABOLITE_INFERENCE_TREE_H
#define METABOLITE_INFERENCE_TREE_H
#include "coretools/Main/TLog.h"
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class TNode {
private:
	std::string _id;              // unique identifier for the node
	int _parentIndex;             // pointer to parent node
	double _branchLengthToParent; // branch length to parent node
	std::vector<int> _children;   // vector to child nodes indices
public:
	// Constructor, initializes a TNode with id, _branchLengthToParent and parent node
	TNode(std::string IdString, double BranchLengthToParent, int Parent);

	// Function to add child
	void addChild(int ChildIndex) { _children.push_back(ChildIndex); };

	// Method to check if the node is a leaf (has no _children)
	[[nodiscard]] std::string id() const { return _id; };
	[[nodiscard]] int parentIndex() const { return _parentIndex; };
	[[nodiscard]] size_t numChildren() const { return _children.size(); };
	[[nodiscard]] std::vector<int> children() { return _children; };
	[[nodiscard]] bool isLeaf() const { return _children.empty(); };
	[[nodiscard]] bool isRoot() const { return _parentIndex < 0; };

	bool operator==(const std::string& Id) const { return _id == Id; };
};

class TTree {
private:
	std::vector<TNode> _nodes; // a map to store nodes with their ids
	std::vector<int> _leaves;
	std::vector<int> _roots;
	std::vector<int> _leafIndices;
	std::vector<int> _rootIndices;

public:
	// Destructor, deletes all nodes
	~TTree();

	// Get node by its id
	TNode get_node(std::string& Id);

	// Method to load the tree from a file
	void load_from_file(const std::string& filename);

	// Find the number of roots in the tree
	[[nodiscard]] int count_roots() const { return _roots.size(); }

	// Method to get all the leaves of the tree
	[[nodiscard]] std::vector<int> get_leaf_nodes() const { return _leaves; }

	// Method to get all the root nodes
	[[nodiscard]] std::vector<int> get_root_nodes() const { return _roots; }
};
#endif // METABOLITE_INFERENCE_TREE_H
