//
// Created by Marco Visani on 26.06.23.
//

#include "TTree.h"
#include "coretools/Files/TFile.h"
#include <iostream>
#include <sstream>

// Node constructor implementation
TNode::TNode(std::string IdString, double BranchLengthToParent, int Parent)
    : _id(IdString), _parentIndex(Parent), _branchLengthToParent(BranchLengthToParent) {}

// Tree destructor implementation
TTree::~TTree() {}

void TTree::load_from_file(const std::string& filename) {
	coretools::instances::logfile().listFlush("Reading tree from file '", filename, "' ...");
	coretools::TInputFile file(filename, coretools::TFile_Filetype::header);

	if (file.numCols() != 3) {
		UERROR("File '", filename, "' is expected to have 3 columns, but has ", file.numCols(), " !");
	}

	// Each line is a vector of strings
	std::vector<std::string> line;

	//
	while (file.read(line)) {
		int parent_index = -1;
		if (line[1] != "NA") {
			auto parent = std::find(_nodes.begin(), _nodes.end(), line[1]);
			if (parent == _nodes.end()) { UERROR("Parent '", line[1], "' of node '", line[0], "' does not exist !"); }
			parent_index = parent - _nodes.begin();
		}

		double branch_length = coretools::str::fromString<double>(line[2]);
		_nodes.emplace_back(line[0], branch_length, parent_index);

		// add child to parent
		if (parent_index > 0) { _nodes[parent_index].addChild(_nodes.size() - 1); }
	}

	// identify roots and leaves
	_leafIndices.resize(_nodes.size(), -1);
	_rootIndices.resize(_nodes.size(), -1);
	for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
		if (it->isLeaf() == 0) {
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

TNode TTree::get_node(std::string& Id) {
	auto node_iterator = std::find(_nodes.begin(), _nodes.end(), Id);
	if (node_iterator == _nodes.end()) { UERROR("Node '", Id, "' does not exist !"); }
	int node_index = node_iterator - _nodes.begin();
	return _nodes[node_index];
}