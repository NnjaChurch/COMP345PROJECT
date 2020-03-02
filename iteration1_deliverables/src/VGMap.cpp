#include "..\headers\VGMap.h"

VGMap::VGMap(int player_number) {
	// Initialize Variables
	PlayerNumber = new int(player_number);
	NumNodes = new int(30);
	Nodes = new vector<VGNode*>;
	Edges = new vector<vector<int>>;

	// Fill Nodes
	for (int i = 0; i < *NumNodes; i++) {
		Nodes->push_back(new VGNode(i));
	}

	// Adjacency List
	vector<vector<int>> tempVec = {
		//	L	R	T	B
		{	-1,	1, -1,	5},		// 0
		{	0,	2, -1,	6},		// 1
		{	1,	3, -1,	7},		// 2
		{	2,	4, -1,	8},		// 3
		{	3,	-1, -1,	9},		// 4
		{	-1,	6,	0,	10},	// 5
		{	5,	7,	1,	11},	// 6
		{	6,	8,	2,	12},	// 7
		{	7,	9,	3,	13},	// 8
		{	8,	-1,	4,	14},	// 9
		{	-1,	11,	5,	15},	// 10
		{	10,	12,	6,	16},	// 11
		{	11, 13, 7,	17},	// 12
		{	12, 14, 8,	18},	// 13
		{	13, -1, 9,	19},	// 14
		{	-1, 16, 10, 20},	// 15
		{	15, 17, 11, 21},	// 16
		{	16, 18, 12, 22},	// 17
		{	17, 19, 13, 23},	// 18
		{	18, -1, 14, 24},	// 19
		{	-1, 21, 15, 25},	// 20
		{	20, 22, 16, 26},	// 21
		{	21, 23, 17, 27},	// 22
		{	22, 24, 18, 28},	// 23
		{	23, -1, 19, 29},	// 24
		{	-1, 26, 20, -1},	// 25
		{	25, 27, 21, -1},	// 26
		{	26, 28, 22, -1},	// 27
		{	27, 29, 23, -1},	// 28
		{	28, -1, 24,	-1},	// 29
	};
	*Edges = tempVec;
}

VGMap::VGMap(int player_number, vector<VGNode*>* nodes, vector<vector<int>>* edges) {
	*PlayerNumber = player_number;
	*NumNodes = nodes->size();
	Nodes = nodes;
	Edges = edges;
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

void VGMap::AddTile(int board_space) {
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
}

VGMap::VGNode::~VGNode() {
	// Clear Node data if necessary
}
