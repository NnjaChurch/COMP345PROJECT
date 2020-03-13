#pragma once+
// Includes
#include <vector>
#include <iostream>

#include "Resources.h"

// Namespaces
using namespace std;

// Main Class
class GBMap {
public:
	// Node Class
	class GBNode {
		// Will contain Tile Data
	public:
		GBNode(int node_number);
		virtual ~GBNode();

		// Node Functions
		void PlaceTile(HarvestTile* tile);
	private:
		int NodeNumber;
		HarvestTile* Tile;
	};

	// Default Constructor
	GBMap();
	// Destructor
	virtual ~GBMap();

	// Player Functions
	void AddTile(int board_space, HarvestTile* tile);

	// Draw Functions
	void Draw();

private:
	int* NumNodes;
	vector<GBNode*>* Nodes;
	vector<vector<int>>* Edges;
};