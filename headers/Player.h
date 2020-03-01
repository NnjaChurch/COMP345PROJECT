#pragma once
// Includes
#include <iostream>
#include<vector> 
#include<ctime>
#include<stack>
// Namespaces
using namespace std;
class Player
{
public:
    
	// Default Constructor
    Player(int player_number);
    // Destructor
    virtual ~Player();
    void PlaceHarvestTile();
    void DrawBuilding();
    void DrawHarvestTile();
    void ResourceTracker();
    void BuildVillage();
    void CalculateResources();


private:
    string *villageName;
    vector<int> *resourceMarkers();
    vector<int> *harvest_tiles();
    vector<int> *building_tokens();
};

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
};
