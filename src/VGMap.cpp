#include "..\headers\VGMap.h"

VGMap::VGMap() {
	NumNodes = 0;
	Nodes = NULL;
	Edges = NULL;
	PlayerNumber = 0;
}

VGMap::VGMap(int player_number) {
	// Set Player Number
	PlayerNumber = new int(player_number);
	// Allocate Space for Data Members
	NumNodes = new int;
	Nodes = new vector<VGNode*>;
	Edges = new vector<vector<int>>(30, vector<int>(4, -1));
}

VGMap::~VGMap() {
	delete PlayerNumber;
	delete NumNodes;
	// Clear Nodes
	for (int i = 0; i < Nodes->size(); i++) {
		// Clear Node
		Nodes->at(i)->~VGNode();
	}
	Nodes->clear();
	delete Nodes;
	// Clear Edges
	Edges->clear();
	delete Edges;
}

void VGMap::AddNodes(int node_count) {
	for (int i = 0; i < node_count; i++) {
		Nodes->push_back(new VGNode(i));
	}
}

void VGMap::AddTile(int board_space, BuildingTile* tile) {
	// Add Tile to position in Game Board (used later)
}

void VGMap::Draw() {
	// TODO: Update Printing to Include Buildings if placed

	// Output to Console
	cout << "Player " << *PlayerNumber << " Village Board\n";
	cout << "________________\n";
	for (int i = 0; i < Nodes->size(); i++) {
		if (i < 10) {
			cout << "| " << i;
		}
		else {
			cout << "|" << i;
		}
		if (i % 5 == 4) {
			cout << "|\n";
			cout << "----------------\n";
		}
	}
	cout << "\n";
}

VGMap::VGNode::VGNode(int node_number) {
	NodeNumber = new int(node_number);
	// Allocate space for Data Members
	NodeValue = new int;
	Tile = new BuildingTile;
}

VGMap::VGNode::~VGNode() {
	delete NodeNumber;
	delete NodeValue;
	delete Tile;
}

void VGMap::VGNode::SetValue(int node_value) {
	*NodeValue = node_value;
}
