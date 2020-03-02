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


// ANNES OLD CODE
/*
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
	};

	// Default Constructor
	VGMap(int player_number);
	// Constructor for Map Loader
	VGMap(int player_number, vector<VGNode*>* nodes, vector<vector<int>>* edges);
	// Destructor
	virtual ~VGMap();

	// Player Functions
	void AddTile(int board_space);		// Missing Tile from Resource
	
	// Draw Functions
	void Draw();	// Outputs Board to the Console

	private:
	int* PlayerNumber;
	int* NumNodes;
	vector<VGNode*>* Nodes;
	vector<vector<int>>* Edges;
};
struct Building;


class TileDeck {
	public:
		stack<vector<char>> deck;
		Building draw(stack<Building>& deck);
		void BuildingDeck();
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
		TileDeck(){
			vector < vector<char>> temp = allCard();
			fullShuffle(temp);
			deck = createDeck(temp);
		};
		void rotate(vector<char>& arr);
		vector < vector<char>> allCard();
		void shuffle(vector <vector<char>>& vec, int a, int b);
		void fullShuffle(vector <vector<char>>& vec);
		stack<vector<char>> createDeck(vector<vector<char>> cards);
		vector<char> draw(stack<vector<char>>& deck);
		
	private:
		


};


class BuildingDeck {

	public:
		BuildingDeck();
		Building draw(stack<struct Building>& deck);

	private:
		stack<struct Building> deckOfBuilding;
		void shuffle(vector<struct Building>& vec, int a, int b);
		void fullShuffle(vector<struct Building>& vec);
		stack<struct Building> createDeck(vector<struct Building> cards);




};

struct Building
{
	int value;
	char color;
};*/
