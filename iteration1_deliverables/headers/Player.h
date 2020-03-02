#pragma once
// Includes
#include <iostream>
#include <vector> 
#include <ctime>
#include <stack>
#include <string>
// Namespaces
using namespace std;

// Temp Classes (removed after linking components)
// Tile to be placed
struct Tile {
	vector<char>* TileData;
};
// GBMap Struct to Place Tiles on
struct GBMap {
	vector<Tile*>* Nodes;
	vector<vector<int>>* Edges;
};
// VGMap Struct to Place Tiles on
struct VGMap {
	string* VillageName;
	vector<Tile*>* Nodes;
	vector<vector<int>>* Edges;
};

// Player Class
class Player
{
public:
	
	// Default Constructor
	Player(int player_number);
	// Destructor
	virtual ~Player();

	// Functions
	int PlaceHarvestTile(int board_space, int harvest_tile_number, GBMap* game_board);
	void DrawBuilding(stack<Tile*>* building_deck);
	void DrawHarvestTile(stack<Tile*>* harvest_deck);
	void ResourceTracker(int board_space, GBMap* game_board);

	// Part 6 Functions
	void BuildVillage(int board_space, int building_tile_number);
	vector<int> CalculateResources(int board_space, GBMap* game_board);


private:
	int* PlayerNumber;
	VGMap* village;
	vector<int>* resource_markers;
	vector<Tile*>* harvest_tiles;
	vector<Tile*>* building_tokens;
};