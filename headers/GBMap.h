#pragma once
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
		bool CheckTile();
		void PlaceTile(HarvestTile* tile);
		void ResetTileAccess();

		// Getter
		HarvestTile* GetTile();

		// Drawing Functions
		vector<string> PrintTile();

	private:
		int NodeNumber;
		HarvestTile* Tile;
	};

	// Default Constructor
	GBMap();
	// Destructor
	virtual ~GBMap();

	// Setters
	void AddNodes(int num_nodes);
	void AddEdge(int edge_start, int side_value, int edge_end);

	void ResetMapAccess();

	// Getters
	vector<int> GetAdjacentTiles(int current_tile);
	int GetNumNodes() const;
	GBNode* GetNode(int board_space) const;

	bool CheckEmpty(int board_space);
	int CountEmpty();

	// Player Functions
	void AddTile(int board_space, HarvestTile* tile);
	void DrawTile(Deck* decks);
	BuildingTile* TakeBuilding(int tile_number, Deck* decks);

	// Draw Functions
	void Draw();
	void PrintTilePool();

private:
	int* NumNodes;
	int* SpacesLeft;
	vector<GBNode*>* Nodes;
	vector<vector<int>>* Edges;
	vector<BuildingTile*>* TilePool;
};