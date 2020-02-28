#pragma once
// Includes
#include <vector>
#include <iostream>

// Namespaces
using namespace std;
class Player
{
   

public:
    
    // Default Constructor
    Player(int player_number);
    // Destructor
    virtual ~Player();

    string PlaceHarvestTile();
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

class TempVGMap {
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
	TempVGMap(int player_number);
	// Constructor for Map Loader
	TempVGMap(int player_number, vector<VGNode*>* nodes, vector<vector<int>>* edges);
	// Destructor
	virtual ~TempVGMap();

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
class TempResources{
    public:
    private:
    vector<int>* villageBuildings;

};