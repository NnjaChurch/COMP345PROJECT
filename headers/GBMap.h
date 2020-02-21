#pragma once

/*
	PLANNING NOTES - FEB 5TH 2020
	--------------------------------------------------
	- Game Board: Array (or Vector) of Nodes
		- 5 x 5 area first (indexes 0 - 24), then the top and bottom (25 - 29 and 30 - 34), then the two sides (35 - 39 and 40 - 44)
		- 45 Nodes in total (4 players), with 35 (3 players) and 25 (2 players)
	- Each Node: Contains 4 SubNodes
		- 4 nodes in the order of [0] - Top Left, [1] - Top Right, [2] - Bottom Left, [3] - Bottom Right
		- Initially blank (other than the 4 already filled corners) and are filled when a player places a tile on it.
	- Adjacency: Vector of Nodes and Vector of Edges:
		- Good source for the explanation: https://www.geeksforgeeks.org/graph-and-its-representations/
		- We would require a second set for subnodes most likely
	- Display (Console?):
		- Should be fairly simple to display the game board onto console:
			- Read through node array in order and display the graph accordingly
			- Different display functions based on number of players since board differs or always display full board with markers to which tiles are active?
*/

// Includes
#include <vector>
#include <iostream>

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
	private:
		int NodeNumber;
	};

	// Default Constructor
	GBMap(int num_players);
	// Constructor for MapLoader
	GBMap(vector<GBNode*>* nodes, vector<vector<int>>* edges);
	// Destructor
	virtual ~GBMap();

	// Player Functions
	void AddTile(int board_space);

	// Draw Functions
	void Draw();	// Outputs Board to the Console

	

private:
	int* NumNodes;
	vector<GBNode*>* Nodes;
	vector<vector<int>>* Edges;
};