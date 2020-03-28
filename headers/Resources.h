
#pragma once
// Includes
#include <vector>
#include <stack>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>

using namespace std;

enum class TileType {
    BUILDING,
    HARVEST
};

enum class ResourceType {
    WOOD,
    STONE,
    SHEEP,
    WHEAT
};

class Resource {
public:
    // Default Constructor
    Resource();
    // Constructor
    Resource(int tile_number);
    // Destructor
    ~Resource();

    // Getter
    int GetTileNumber();

private:
    int* TileNumber;
};


class BuildingTile : public Resource{
public:
    // Default Constructor
    BuildingTile();
    // Constructor
    BuildingTile(int tile_number, int value, ResourceType type);
    // Destructor
    ~BuildingTile();

    // Setters
    void setValue(int value);
    void setType(ResourceType type);
    void setFlipped(bool flip);

    // Getters
    int getValue();
    ResourceType getType();
    bool getFlipped();

    // Drawing Functions
    string PrintType();
    vector<string> PrintBuildingTile();

private:
    int* Value;
    ResourceType* Type;
    bool* Flipped;
};

class HarvestTile : public Resource {
public:
    // Default Constructor
    HarvestTile();
    // Constructor
    HarvestTile(int number, vector<ResourceType> resource_list);
    // Destructor
    ~HarvestTile();

    // HarvestNode
    class HarvestNode {
    public:
        HarvestNode();
        // Constructor
        HarvestNode(ResourceType type);
        // Destructor
        ~HarvestNode();

        // Getters
        ResourceType getType();

        // Setters
        void ResetNodeAccess();

        // Drawing Functions
        string PrintNode();

    private:
        ResourceType* Type;
        bool* Visited;
    };

    // Getters
    vector<HarvestNode*>* GetTileData();

    // Drawing Functions
    vector<string> PrintHarvestTile();
    
    // Tile Functions
    void ResetTileAccess();
    void rotate();

    // Attributes
    vector<HarvestNode*>* Nodes;

};

class Deck {
public:
    // Default Constructor
    Deck();
    // Destructor
    ~Deck();

    // Functions
    HarvestTile* DrawHarvestTile();
    BuildingTile* DrawBuilding();

private:
    stack<HarvestTile*>* HarvestDeck;
    stack<BuildingTile*>* BuildingDeck;
};