#include "../headers/GBMap.h"

GBMap::GBMap() {
	NumNodes = new int();
	Nodes = new vector<GBNode*>;
	Edges = new vector<vector<int>>;
}

GBMap::~GBMap() {
	delete NumNodes;
	// Delete inner Nodes
	Nodes->clear();
	// Clear allocated memory for vector
	delete Nodes;
	// Delete Edges
	Edges->clear();
	delete Edges;
}

void GBMap::AddNodes(int num_nodes) {
	*NumNodes = num_nodes;
	for (int i = 0; i < num_nodes; i++) {
		Nodes->push_back(new GBNode(i));
	}
	Edges = new vector<vector<int>>(num_nodes, vector<int>(4, -1));
}

void GBMap::AddEdge(int edge_start, int side_value, int edge_end) {
	Edges->at(edge_start).at(side_value) = edge_end;
}

void GBMap::ResetMapAccess() {
	for (int i = 0; i < Nodes->size(); i++) {
		Nodes->at(i)->ResetTileAccess();
	}
}

vector<int> GBMap::GetAdjacentTiles(int current_tile) {
	return Edges->at(current_tile);
}

bool GBMap::CheckEmpty(int board_space) {
	return Nodes->at(board_space)->CheckTile();
}

void GBMap::AddTile(int board_space, HarvestTile* tile) {
	Nodes->at(board_space)->PlaceTile(tile);
}

void GBMap::Draw() {
	// TODO: Print function to draw GBMap
}

GBMap::GBNode::GBNode(int node_number) {
	NodeNumber = node_number;
	Tile = NULL;
}

GBMap::GBNode::~GBNode() {
	Tile->~HarvestTile();
}

bool GBMap::GBNode::CheckTile() {
	if (Tile == NULL) {
		return false;
	}
	else {
		return true;
	}
}

void GBMap::GBNode::PlaceTile(HarvestTile* tile) {
	Tile = tile;
}

void GBMap::GBNode::ResetTileAccess() {
	if (CheckTile()) {
		Tile->ResetTileAccess();
	}
}
