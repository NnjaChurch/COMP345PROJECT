#pragma once
// Includes
#include <vector>
#include <iostream>

// Namespaces
using namespace std;
class Player
{   
    public:
    void PlaceHarvestTile(int board_space);
    void DrawBuilding(int PlayerNumber);
    void DrawHarvestTile();
    void ResourceTracker();
    void BuildVillage();
    void CalculateResources();

    // Default Constructor
	Player(int player_number);
    // Destructor
	virtual ~Player();

    private:
    string* villageName;
    vector<int>* resourceMarkers[4];
    vector<int>* harvest_tiles[];
    vector<int>* building_tokens[];
};

