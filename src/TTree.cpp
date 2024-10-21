//
// Created by Marco Visani on 26.06.23.
//

#include "TTree.h"
#include "coretools/Files/TInputFile.h"
#include <iostream>
#include <sstream>
#include <utility>

// Tree destructor implementation
TTree::~TTree() = default;

void TTree::load_from_file(const std::string &filename) {
	coretools::instances::logfile().listFlush("Reading tree from file '", filename, "' ...");
	coretools::TInputFile file(filename, coretools::FileType::Header);

	if (file.numCols() != 3) {
		UERROR("File '", filename, "' is expected to have 3 columns, but has ", file.numCols(), " !");
	}

	//
	for (; !file.empty(); file.popFront()) {
		bool is_root        = true;
		size_t parent_index = 0;
		if (file.get(1) != "NA") {
			// we read line by line the edge list from the file
			// if the child node (column 0) is not in the tree, we add the node,
			// if the parent is not in the tree, we add the node and set the parent as root
			// as long as it has no parents.
			//
			//
			// auto parent = std::find(_nodes.begin(), _nodes.end(), file.get(1));
			// if (parent == _nodes.end()) {
			// 	UERROR("Parent '", file.get(1), "' of node '", file.get(0), "' does not exist !");
			// }
			// TODO implement our way
			parent_index = parent - _nodes.begin();
		}

		auto branch_length = file.get<double>(2);
		_nodes.emplace_back(file.get(0), branch_length, parent_index, is_root);

		// add child to parent
		if (!is_root) { _nodes[parent_index].addChild(_nodes.size() - 1); }
	}

	// identify roots and leaves
	_leafIndices.resize(_nodes.size(), -1);
	_rootIndices.resize(_nodes.size(), -1);
	for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
		if (it->isLeaf()) {
			_leafIndices[it - _nodes.begin()] = _leaves.size();
			_leaves.push_back(it - _nodes.begin());
		} else if (it->isRoot()) {
			_rootIndices[it - _nodes.begin()] = _roots.size();
			_roots.push_back(it - _nodes.begin());
		}
	}

	coretools::instances::logfile().done();
	coretools::instances::logfile().conclude("Read ", _nodes.size(), " nodes of which ", _roots.size(),
	                                         " are roots and ", _leaves.size(), " are leaves.");
}

TNode TTree::get_node(std::string &Id) {
	auto node_iterator = std::find(_nodes.begin(), _nodes.end(), Id);
	if (node_iterator == _nodes.end()) { UERROR("Node '", Id, "' does not exist !"); }
	int node_index = node_iterator - _nodes.begin();
	return _nodes[node_index];
}
