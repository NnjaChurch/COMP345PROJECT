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
	Nodes = new vector<VGNode*>();
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

void VGMap::AddNode(int node_number, int node_value) {
	Nodes->push_back(new VGNode(node_number, node_value));
}

void VGMap::AddEdge(int edge_start, int side_value, int edge_end) {
	Edges->at(edge_start).at(side_value) = edge_end;
}

vector<int> VGMap::GetAdjacentTiles(int board_space) {
	return Edges->at(board_space);
}

bool VGMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

void VGMap::AddTile(int board_space, BuildingTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
}

void VGMap::Draw() {
	// TODO: Print functions for VGMap
}

VGMap::VGNode::VGNode(int node_number, int node_value) {
	NodeNumber = new int(node_number);
	// Allocate space for Data Members
	NodeValue = new int(node_value);
	Tile = NULL;
}

VGMap::VGNode::~VGNode() {
	delete NodeNumber;
	delete NodeValue;
	delete Tile;
}

bool VGMap::VGNode::CheckTile() {
	if (Tile == NULL) {
		return false;
	}
	else {
		return true;
	}
}

void VGMap::VGNode::PlaceTile(BuildingTile* tile) {
	Tile = tile;
}