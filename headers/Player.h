#pragma once
// Includes
#include <iostream>
#include <vector> 
#include <ctime>
#include <stack>
#include <string>

#include "GBMap.h"
#include "VGMap.h"
#include "Resources.h"
// Namespaces
using namespace std;

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
	void DrawBuilding(Deck* decks);
	void DrawHarvestTile(Deck* decks);

	// Hand Functiions
	void ShowHand();
	void ResourceTracker(int board_space, GBMap* game_board);

	// Part 6 Functions
	void BuildVillage(int board_space, int building_tile_number);
	vector<int>* CalculateResources(int board_space, GBMap* game_board);

	vector<int>* CalculateTile(GBMap* game_board, vector<int> adjacent, HarvestTile* current_tile, int adj_index, int node_index, int compare_index);

private:
	int* PlayerNumber;
	VGMap* village;
	vector<int>* resource_markers;
	vector<HarvestTile*>* harvest_tiles;
	vector<BuildingTile*>* building_tokens;
};
