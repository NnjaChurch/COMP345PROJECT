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
    string *villageName;
    vector<int> *resourceMarkers();
    vector<int> *harvest_tiles();
    vector<int> *building_tokens();
};
class TempVGMap
    {
    public:
        // Node Class
        class TempTempsVGNode
        {
            // Will contain Tile data
        public:
            TempsVGNode(int node_number);
            virtual ~TempsVGNode();

        private:
            int NodeNumber;
        };

        // Default Constructor
        TempsVGMap(int player_number);
        // Constructor for Map Loader
        TempsVGMap(int player_number, vector<TempsVGNode *> *nodes, vector<vector<int>> *edges);
        // Destructor
        virtual ~TempsVGMap();

        // Player Functions
        void AddTile(int board_space); // Missing Tile from Resource

        // Draw Functions
        void Draw(); // Outputs Board to the Console

    private:
        int *PlayerNumber;
        int *NumNodes;
        vector<TempsVGNode*> *Nodes;
        vector<vector<int>> *Edges;
    };