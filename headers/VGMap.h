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
	public:
		VGNode(int node_number);
		virtual ~VGNode();

		// Node Functions
		void SetValue(int node_value);
		void PlaceTile(BuildingTile* tile);
	private:
		int* NodeNumber;
		int* NodeValue;
		BuildingTile* Tile;
	};

	// Default Constructor
	VGMap();
	// Constructor
	VGMap(int player_number);

	// Destructor
	virtual ~VGMap();

	// Setter Functions
	void AddNodes(int node_count);

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

