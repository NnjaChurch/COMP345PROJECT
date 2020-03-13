#pragma once
// Includes
#include <vector>
#include <iostream>

#include "Resources.h"

// Namespaces
using namespace std;

class VGMap {
public:
	// Node Class
	class VGNode {
		// Will contain Tile data
	public:
		VGNode(int node_number);
		virtual ~VGNode();
	private:
		int NodeNumber;
		BuildingTile* Tile;
	};

	// Default Constructor
	VGMap();
	// Constructor
	VGMap(int player_number);

	// Destructor
	virtual ~VGMap();

	// Player Functions
	void AddTile(int board_space, BuildingTile* tile);

	// Draw Functions
	void Draw();

private:
	int* PlayerNumber;
	int* NumNodes;
	vector<VGNode*>* Nodes;
	vector<vector<int>>* Edges;
};

