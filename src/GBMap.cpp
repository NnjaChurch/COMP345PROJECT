#include "../headers/GBMap.h"

GBMap::GBMap() {
	NumNodes = new int;
	Nodes = new vector<GBNode*>;
	Edges = new vector<vector<int>>;
}

GBMap::~GBMap() {
	delete NumNodes;
	// Delete Nodes
	for (int i = 0; i < Nodes->size(); i++) {
		// Call Node Deconstructor
		Nodes->at(i)->~GBNode();
		// Clear allocated memory for Node
		delete Nodes->at(i);
	}
	// Clear allocated memory for vector
	delete Nodes;
	// Delete Edges
	Edges->clear();
	delete Edges;
}

void GBMap::AddTile(int board_space, HarvestTile* tile) {
	// Add Tile to position in Game Board (used later)
}

void GBMap::Draw() {
	// TODO: Update Print to include harvest tiles if placed

	// Print for 25 Nodes
	// Print for 35 Nodes
	// Print for 45 Nodes

	// Temp Print to check adjacencies
	cout << "Number of Nodes: " << *NumNodes << endl;
	cout << "Adjacencies:" << endl;
	cout << "\tL\tR\tT\tB" << endl;
	for (int i = 0; i < Edges->size(); i++) {
		cout << i << ":\t";
		for (int j = 0; j < (*Edges)[i].size(); j++) {
			cout << (*Edges)[i][j] << "\t";
		}
		cout << "\n";
	}
}

GBMap::GBNode::GBNode(int node_number) {
	NodeNumber = node_number;
	Tile = new HarvestTile;
}

GBMap::GBNode::~GBNode() {
	Tile->~HarvestTile();
}