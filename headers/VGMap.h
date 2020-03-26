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
		VGNode(int node_number, int node_value);
		virtual ~VGNode();

		// Node Functions
		bool CheckTile();
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
	void AddNode(int node_number, int node_value);
	void AddEdge(int edge_start, int side_value, int edge_end);

	// Getter Functions
	bool CheckEmpty(int board_space);

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

