#include "..\headers\VGMap.h"

VGMap::VGMap() {
	NumNodes = 0;
	Nodes = NULL;
	Edges = NULL;
	PlayerNumber = 0;
}

VGMap::VGMap(int player_number) {
	
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

void VGMap::AddTile(int board_space, BuildingTile* tile) {
	// Add Tile to position in Game Board (used later)
}

void VGMap::Draw() {
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
	NodeNumber = node_number;
	// Default Set Tile to Empty Tile
	Tile = new BuildingTile;
}

VGMap::VGNode::~VGNode() {
	// Clear Tile
	Tile->~BuildingTile();
}
