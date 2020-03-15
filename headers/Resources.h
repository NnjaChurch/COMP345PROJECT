#pragma once
// Includes
#include <vector>
#include <stack>
#include <iostream>
#include <ctime>

// Namepsaces
using namespace std;

// Sub Classes
enum ResourceType {
	WOOD,
	STONE,
	SHEEP,
	WHEAT
};

enum TileType {
	BUILDING,
	HARVEST
};

class Resource {
public:
	// Default Constructor
	Resource();
	// Constructor
	Resource(int tile_number);
	// Destructor
	~Resource();

private:
	int* TileNumber;
};

class BuildingTile : public Resource {
public:
	// Default Constructor
	BuildingTile();
	// Constructor
	BuildingTile(int tile_value, ResourceType tile_type);
	// Destructor
	~BuildingTile();
private:
	// Attributes
	int* Value;
	ResourceType* Type;
	bool* Flipped;
};

class HarvestTile : public Resource {
public:
	// Default Constructor
	HarvestTile();
	// Constructor
	HarvestTile(int tile_number);
	// Destructor
	~HarvestTile();
private:
	// HarvestNode
	class HarvestNode {
	public:
		// Constructor
		HarvestNode(ResourceType type);
		// Destructor
		~HarvestNode();
	private:
		ResourceType* Type;
		bool* Visited;
	};
	// Attributes
	vector<HarvestNode>* Nodes;
	
};

class Deck {
public:
	// Default Constructor
	Deck();
	// Constructor
	Deck(TileType type);
	// Destructor
	~Deck();

	// Functions
	Resource DrawTile();
	void Shuffle();
private:
	TileType* DeckType;
	stack<Resource>* Tiles;
};


// Karim Code
/*
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
using namespace std;
struct Building
{
	char color;
	int value;
};
void buildingFullShuffle(vector<Building>& vec);
class Resources {
	public:
		// Constructor
		Resources();
		// Destructor
		~Resources();

		// Functions
		vector<char> drawTile();
		Building drawBuilding();

		// Inner Tile Functions
		char getTopLeftOfTile(vector<char>);
		char getTopRightOfTile(vector<char>);
		char getBottomLeftOfTile(vector<char>);
		char getBottomRightOfTile(vector<char>);
		void rotate(vector<char>& arr);

		vector < vector<char>> allCard();


		// Shufflers
		void buildingShuffle(vector<Building>& vec, int a, int b);
		void BuildingFullShuffle(vector<Building>& vec);
		stack<Building> createDeckOfBuilding(vector<Building> cards);

		stack<vector<char>> createDeckOfTile(vector<vector<char>> cards);
		void tileFullShuffle(vector <vector<char>>& vec);
		void tileShuffle(vector <vector<char>>& vec, int a, int b);

		
	private:


		// Attributes
		
		stack<Building> buildingDeck;
		stack<vector<char>> tileDeck;
};
*/