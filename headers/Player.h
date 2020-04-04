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

	// Hand Functions
	void ShowHand();
	int ResourceTracker();

	// Setters
	void AssignVillage(VGMap* village);

	// Getters

	// Tile Functions
	int PlaceHarvestTile(int board_space, int harvest_tile_number, GBMap* game_board);
	int PlaceShipmentTile(int board_space, GBMap* game_board);
	void DrawBuilding(Deck* decks);
	void DrawHarvestTile(Deck* decks);
	void DrawShipmentTile(Deck* decks);

	int BuildVillage(int board_space, int building_tile_number);
	vector<int>* CalculateResources(int board_space, GBMap* game_board);

	// Recursive Calculation Functions
	vector<int>* CalculateTL(GBMap* game_board, int board_space, HarvestTile* tile);
	vector<int>* CalculateTR(GBMap* game_board, int board_space, HarvestTile* tile);
	vector<int>* CalculateBL(GBMap* game_board, int board_space, HarvestTile* tile);
	vector<int>* CalculateBR(GBMap* game_board, int board_space, HarvestTile* tile);

	// Calculation Functions
	vector<int>* CalculateNode_ADJ(GBMap* game_board, vector<int> adjacent, HarvestTile* cur_tile, int tile_index, int node_index, int adj_index);
	vector<int>* CalculateNode_CUR(GBMap* game_board, HarvestTile* cur_tile, int tile_index, int node_index, int adj_index);
	vector<int>* GatherResources(ResourceType type);

private:
	int* PlayerNumber;
	VGMap* Village;
	vector<int>* Resource_Markers;
	vector<HarvestTile*>* Harvest_Tiles;
	vector<BuildingTile*>* Building_Tiles;
	HarvestTile* Shipment_Tile;
};
