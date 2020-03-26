
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
    void printType();
    void printBuildingTile();

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

    // Drawing Functions
    void printHarvestTile();
    
    // Tile Functions
    void rotate();

    // HarvestNode
    class HarvestNode {
    public:
        HarvestNode();
        // Constructor
        HarvestNode(ResourceType type);
        // Destructor
        ~HarvestNode();

        ResourceType getType();
        void PrintNode();
        ResourceType* Type;
        bool* Visited;
    };
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